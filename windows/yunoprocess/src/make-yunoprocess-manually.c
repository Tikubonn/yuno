#include <yuno.private>
#include <windows.h>
#include <psapi.h>

/*
	process のメモリ使用量を SIZE_T 型で返す関数です。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int get_process_memory_size (HANDLE process, SIZE_T *memsizep){
	PROCESS_MEMORY_COUNTERS counter;
	if (GetProcessMemoryInfo(process, &counter, sizeof(counter)) == 0){
		return 1;
	}
	*memsizep = counter.PeakWorkingSetSize;
	return 0;
}

/*
	copy_process_memory_area 関数で使用されるバッファの大きさを表す整数です。
*/

#define COPY_PROCESS_MEMORY_AREA_BUFFER_SIZE 4096

/*
	processfrom の指定された領域を processto にコピーする関数です。
	Windows API に詳しくないことと、ひとまず期待する振る舞いをしてくれればよいため、
	ある程度の例外は捕捉しても無視するように書いています。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int copy_process_memory_area (void *newaddr, void *address, SIZE_T size, HANDLE processfrom, HANDLE processto){
	char buffer[COPY_PROCESS_MEMORY_AREA_BUFFER_SIZE];
	for (SIZE_T readoffset = 0; readoffset < size;){
		SIZE_T readsize;
		if (ReadProcessMemory(processfrom, address + readoffset, buffer, min(size - readoffset, sizeof(buffer)), &readsize) == 0){
			DWORD errorno = GetLastError();
			if (errorno == ERROR_NOACCESS || 
					errorno == ERROR_PARTIAL_COPY){
				break;
			}
			else {
				return 1;
			}
		}
		for (SIZE_T writeoffset = 0; writeoffset < readsize;){
			SIZE_T wrotesize;
			if (WriteProcessMemory(processto, newaddr + readoffset + writeoffset, buffer + writeoffset, readsize - writeoffset, &wrotesize) == 0){
				DWORD errorno = GetLastError();
				if (errorno == ERROR_NOACCESS || 
						errorno == ERROR_PARTIAL_COPY){
					break;
				}
				else {
					return 1;
				}
			}
			writeoffset += wrotesize;
		}
		readoffset += readsize;
	}
	return 0;
}

/*
	noaccess 等が指定されてしまっているプロセスのメモリ領域を確保します。
	この関数は指示された領域をいちど予約したのちに解放し、さらに解放した領域を再確保する手順で確保を試みます。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int allocate_process_memory_area_forcely (void *address, SIZE_T size, HANDLE process, void **newaddrp){
	void *newaddr1 = VirtualAllocEx(process, address, size, MEM_RESERVE, PAGE_READWRITE);
	if (newaddr1 == NULL){
		return 1;
	}
	if (VirtualFreeEx(process, address, size, MEM_DECOMMIT) == 0){
		return 1;
	}
	void *newaddr2 = VirtualAllocEx(process, address, size, MEM_COMMIT, PAGE_READWRITE);
	if (newaddr2 == NULL){
		return 1;
	}
	*newaddrp = newaddr2;
	return 0;
}

/*
	processfrom の領域を processto に複製する振る舞いは copy_process_memory_area と同様ですが、
	この関数は書き込み先の領域を事前に VirtualAllocEx で確保します。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int copy_process_memory_area_with_valloc (void *address, SIZE_T size, HANDLE processfrom, HANDLE processto){
	void *newaddr = VirtualAllocEx(processto, address, size, MEM_COMMIT, PAGE_READWRITE);
	if (newaddr == NULL){
		switch (GetLastError()){
			case ERROR_INVALID_ADDRESS: {
				/*
					アドレスが利用不可能な状態(対象の領域が noaccess 状態など)であれば、
					allocate_process_memory_area_forcely 関数を用いて領域の確保を試みます。
					失敗した場合にはコピーの操作を断念し 1 を返します。
				*/
				void *newaddr2;
				if (allocate_process_memory_area_forcely(address, size, processto, &newaddr2) != 0){
					return 1;
				}
				return copy_process_memory_area(newaddr2, address, size, processfrom, processto);
			}
			case ERROR_INVALID_PARAMETER: {
				return 0; // ignore error!
			}
			default: {
				return 1;
			}
		}
		return 0; // ignore error!
	}
	return copy_process_memory_area(newaddr, address, size, processfrom, processto);
}

/*
	processfrom の複製可能な領域を processto にコピーします。
	この関数のおかげで fork 関数のように、現在の状態を引き継いだプロセスを作成できるようになります。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int copy_process_memory (HANDLE processfrom, HANDLE processto, yunoshared_memory **sharedmemoryp){
	SIZE_T memsize;
	if (get_process_memory_size(processfrom, &memsize) != 0){
		return 1;
	}
	SIZE_T readsize = 0;
	SIZE_T offset = 0;
	while (readsize < memsize){
		MEMORY_BASIC_INFORMATION meminfo;
		if (VirtualQueryEx(processfrom, (void*)offset, &meminfo, sizeof(meminfo)) == 0){
			return 1;
		}
		if (meminfo.State == MEM_COMMIT){
			readsize += meminfo.RegionSize;
		}
		if (meminfo.State == MEM_COMMIT && 
				meminfo.Protect == PAGE_READWRITE){
			/*
				アドレスが共有メモリでなければ領域の複製を行います。
			*/
			if (yunoshared_memory_managed_addressp(meminfo.BaseAddress, sharedmemoryp) == false){
				/*
					使用済み且つ読み書き可能な領域があれば
					そのデータを processto の同じ位置の領域に書き込みます。
				*/
				if (meminfo.Type == MEM_IMAGE){
					/*
						領域が MEM_IMAGE の場合にはデータを直書きする。
					*/
					if (copy_process_memory_area(
						meminfo.BaseAddress,
						meminfo.BaseAddress,
						meminfo.RegionSize,
						processfrom, 
						processto) != 0){
						return 1;
					}
				}
				else if (meminfo.Type == MEM_PRIVATE){
					/*
						領域が MEM_PRIVATE の場合には 
						VirtualAlloc 関数で領域を確保しデータを書き込みます。
					*/
					if (copy_process_memory_area_with_valloc(
						meminfo.BaseAddress,
						meminfo.RegionSize,
						processfrom, 
						processto) != 0){
						return 1;
					}
				}
			}
		}
		offset += meminfo.RegionSize;
	}
	return 0;
}

/*
	現在実行しているコマンドと環境から類似するプロセスを作成しプロセスとメインスレッドを返します。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int clone_process (HANDLE *processp, HANDLE *threadp){
	char *commandline = GetCommandLine();
	STARTUPINFO startupinfo;
	GetStartupInfo(&startupinfo);
	PROCESS_INFORMATION processinfo;
	if (CreateProcess(NULL, commandline, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &startupinfo, &processinfo) == 0){
		return 1;
	}
	*processp = processinfo.hProcess;
	*threadp = processinfo.hThread;
	return 0;
}

/*
	指示された処理を実行後にプロセスが終了するように書かれたラッパー関数です。
	entrypoint の実行結果がそのままプロセスの終了コードになります。
*/

static DWORD __yunocall __subprocess_entry_point (LPVOID parameter){
	yunoprocess *process = parameter;
	if (remap_yunoshared_memory(process->sharedmemoryp) != 0){
		return 1;
	}
	int exitcode = 
		process->entrypoint(
			process->parameter);
	ExitProcess(exitcode); // exit process!
	return 0;
}

/*
	make_yunoprocess_manually 関数の本処理です。
	現在のスレッドの複製を作成し process を初期化します。
	関数が成功した場合には 0 失敗した場合には非ゼロの整数を返します。
*/

static int make_subprocess (yunoprocess_entry_point entrypoint, void *parameter, yunoprocess *processp, yunoshared_memory **sharedmemoryp){
	/*
		まずプロセスを複製する前に関数と引数のアドレスを process に代入します。
		これをしないと複製先のプロセスがどのアドレスを呼べばよいのかわからなくなるからです。
		process, thread, remotethread のメンバは複製先では使わないので未定でも OK です。
	*/
	processp->entrypoint = entrypoint;
	processp->parameter = parameter;
	processp->sharedmemoryp = sharedmemoryp;
	HANDLE process;
	HANDLE thread;
	if (clone_process(&process, &thread) != 0){
		return 1;
	}
	HANDLE currentprocess = GetCurrentProcess();
	if (copy_process_memory(currentprocess, process, sharedmemoryp) != 0){
		/*
			例外を捕捉した場合にはプロセスを中断しハンドルを解放します。
		*/
		if (TerminateProcess(process, 1) == 0){
			return 1;
		}
		if (CloseHandle(process) == 0){
			return 1;
		}
		if (CloseHandle(thread) == 0){
			return 1;
		}
		return 1;
	}
	HANDLE remotethread = CreateRemoteThread(process, NULL, 0, __subprocess_entry_point, processp, CREATE_SUSPENDED, NULL);
	if (remotethread == NULL){
		/*
			例外を捕捉した場合にはプロセスを中断しハンドルを解放します。
		*/
		if (TerminateProcess(process, 1) == 0){
			return 1;
		}
		if (CloseHandle(process) == 0){
			return 1;
		}
		if (CloseHandle(thread) == 0){
			return 1;
		}
		return 1;
	}
	processp->process = process;
	processp->thread = thread;
	processp->remotethread = remotethread;
	return 0;
}

/*
	make_yunoprocess_manually で使用されるミューテックスの名前です。
*/

#define MAKE_YUNOPROCESS_MANUALLY_MUTEX_NAME "MUTEX_FOR_MAKE_YUNOPROCESS_MANUALLY"

yunoprocess_status __yunocall __make_yunoprocess_manually (yunoprocess_entry_point entrypoint, void *parameter, yunoprocess *process, yunoshared_memory **sharedmemoryp){
	/*
		プロセスの複製中に別スレッドにメモリを書き換えられるのは嫌なので
		ミューテックスを用いた排他制御を行っています。
	*/
	HANDLE mutex = CreateMutex(NULL, FALSE, MAKE_YUNOPROCESS_MANUALLY_MUTEX_NAME);
	switch (WaitForSingleObject(mutex, INFINITE)){
		case WAIT_OBJECT_0: {
			if (make_subprocess(entrypoint, parameter, process, sharedmemoryp) != 0){
				return YUNOPROCESS_ERROR;
			}
			if (ReleaseMutex(mutex) == 0){
				return YUNOPROCESS_ERROR;
			}
			if (CloseHandle(mutex) == 0){
				return YUNOPROCESS_ERROR;
			}
			return YUNOPROCESS_SUCCESS;
		}
		default: {
			if (CloseHandle(mutex) == 0){
				return YUNOPROCESS_ERROR;
			}
			return YUNOPROCESS_ERROR;
		}
	}
}
