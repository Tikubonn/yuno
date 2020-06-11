#include <yuno.h>
#include <windows.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

#define BUFFER_SIZE 4096

/*
	プロセスの指定されたメモリ領域を別プロセスに複製します
*/

static inline int copy_memory_area (void *baseaddr, SIZE_T size, HANDLE processfrom, HANDLE processto){
	reset_yunoerror();
	char buffer[BUFFER_SIZE];
	for (SIZE_T offsetread = 0; offsetread < size;){
		SIZE_T readsize;
		if (ReadProcessMemory(processfrom, (char*)baseaddr + offsetread, buffer, min(size - offsetread, sizeof(buffer)), &readsize) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		for (SIZE_T offsetwrite = 0; offsetwrite < readsize;){
			SIZE_T wrotesize;
			if (WriteProcessMemory(processto, (char*)baseaddr + offsetread + offsetwrite, buffer + offsetwrite, readsize - offsetwrite, &wrotesize) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			offsetwrite += wrotesize;
		}
		offsetread += readsize;
	}
	return 0;
}

/*
	局所変数の値を別プロセスに複製します
*/

static inline int copy_local_memory (HANDLE processfrom, HANDLE processto){
	reset_yunoerror();
	for (void *baseaddr = (void*)0; true;){
		MEMORY_BASIC_INFORMATION meminfo;
		if (0 < VirtualQueryEx(processfrom, baseaddr, &meminfo, sizeof(meminfo))){
			if (meminfo.State == MEM_COMMIT && 
					meminfo.Type == MEM_PRIVATE && 
					meminfo.AllocationProtect == PAGE_READWRITE && 
					meminfo.Protect == PAGE_READWRITE){
				MEMORY_BASIC_INFORMATION meminfo2;
				if (VirtualQueryEx(processto, baseaddr, &meminfo2, sizeof(meminfo2)) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (meminfo.AllocationBase == meminfo2.AllocationBase && 
						meminfo2.State == MEM_RESERVE){
					if (VirtualAllocEx(processto, meminfo.BaseAddress, meminfo.RegionSize, MEM_COMMIT, PAGE_READWRITE) == NULL){
						//return 1;
					}
					if (copy_memory_area(meminfo.BaseAddress, meminfo.RegionSize, processfrom, processto) != 0){
						//return 1;
					}
				}
			}
			baseaddr = meminfo.BaseAddress + meminfo.RegionSize;
		}
		else {
			DWORD lasterror = GetLastError();
			if (lasterror == ERROR_INVALID_PARAMETER){
				break;
			}
			else {
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
		}
	}
	return 0;
}

/*
	大域変数の値を別プロセスに複製します
*/

#define MAX_GLOBAL_OFFSET 0x01000000

static inline int copy_global_memory (HANDLE processfrom, HANDLE processto){
	reset_yunoerror();
	for (void *baseaddr = (void*)0; true;){
		MEMORY_BASIC_INFORMATION meminfo;
		if (0 < VirtualQueryEx(processfrom, baseaddr, &meminfo, sizeof(meminfo))){
			if (meminfo.State == MEM_COMMIT && 
					meminfo.Type == MEM_IMAGE && 
					meminfo.AllocationProtect == PAGE_EXECUTE_WRITECOPY && 
					meminfo.Protect == PAGE_READWRITE && 
					meminfo.BaseAddress < (void*)MAX_GLOBAL_OFFSET){
				MEMORY_BASIC_INFORMATION meminfo2;
				if (VirtualQueryEx(processto, baseaddr, &meminfo2, sizeof(meminfo2)) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (meminfo.AllocationBase == meminfo2.AllocationBase && 
						meminfo2.State == MEM_COMMIT && 
						meminfo2.Type == MEM_IMAGE && 
						meminfo2.AllocationProtect == PAGE_EXECUTE_WRITECOPY && 
						meminfo2.Protect == PAGE_WRITECOPY){
					if (copy_memory_area(meminfo.BaseAddress, meminfo.RegionSize, processfrom, processto) != 0){
						//return 1;
					}
				}
			}
			baseaddr = meminfo.BaseAddress + meminfo.RegionSize;
		}
		else {
			DWORD lasterror = GetLastError();
			if (lasterror == ERROR_INVALID_PARAMETER){
				break;
			}
			else {
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
		}
	}
	return 0;
}

/*
	SECURITY_ATTRIBUTES を適切に初期化します
*/

static inline void setup_security_attributes (SECURITY_ATTRIBUTES *secattrs){
	secattrs->nLength = sizeof(SECURITY_ATTRIBUTES);
	secattrs->lpSecurityDescriptor = NULL;
	secattrs->bInheritHandle = TRUE;
}

/*
*/

static inline int clone_process (HANDLE *newprocessp, HANDLE *newthreadp){
	reset_yunoerror();
	char *commandline = GetCommandLine();
	STARTUPINFO startupinfo;
	GetStartupInfo(&startupinfo);
	PROCESS_INFORMATION processinfo;
	SECURITY_ATTRIBUTES secattrs;
	setup_security_attributes(&secattrs);
	if (CreateProcess(NULL, commandline, &secattrs, &secattrs, TRUE, CREATE_SUSPENDED, NULL, NULL, &startupinfo, &processinfo) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	*newprocessp = processinfo.hProcess;
	*newthreadp = processinfo.hThread;
	return 0;
}

/**/

typedef struct process_argument {
	yunoprocess *process;
	yunoshared_memory **globalsharedmemoryp;
} process_argument;

/*
*/

static DWORD __stdcall entrypoint_wrapper (LPVOID parameter){
	process_argument *pargument = parameter;
	reset_yunoerror();
	if (remap_yunoshared_memory(pargument->globalsharedmemoryp) != 0){
		ExitProcess(1);
		return 1;
	}
	int exitcode = pargument->process->entrypoint(pargument->process->parameter);
	ExitProcess(exitcode);
	return 0;
}

/*
*/

static int __stdcall make_process (yunoentrypoint entrypoint, void *parameter, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp, yunoprocess *processp){
	reset_yunoerror();
	HANDLE currentprocess = GetCurrentProcess();
	HANDLE clonedprocess;
	HANDLE clonedthread;
	if (clone_process(&clonedprocess, &clonedthread) != 0){
		return 1;
	}
	processp->entrypoint = entrypoint;
	processp->parameter = parameter;
	processp->process = clonedprocess;
	processp->thread = clonedthread;
	processp->closedp = false;
	process_argument pargument;
	pargument.process = processp;
	pargument.globalsharedmemoryp = globalsharedmemoryp;
	if (remap_yunomemory(clonedprocess, globalmemoryp) != 0){
		TerminateProcess(clonedprocess, 1);
		CloseHandle(clonedprocess);
		CloseHandle(clonedthread);
		return 1;
	}
	if (copy_local_memory(currentprocess, clonedprocess) != 0){
		TerminateProcess(clonedprocess, 1);
		CloseHandle(clonedprocess);
		CloseHandle(clonedthread);
		return 1;
	}
	if (copy_global_memory(currentprocess, clonedprocess) != 0){
		TerminateProcess(clonedprocess, 1);
		CloseHandle(clonedprocess);
		CloseHandle(clonedthread);
		return 1;
	}
	SECURITY_ATTRIBUTES secattrs;
	setup_security_attributes(&secattrs);
	HANDLE remotethread = CreateRemoteThread(clonedprocess, &secattrs, 0, entrypoint_wrapper, &pargument, CREATE_SUSPENDED, NULL);
	if (remotethread == NULL){
		set_yunoerror(YUNOOS_ERROR);
		TerminateProcess(clonedprocess, 1);
		CloseHandle(clonedprocess);
		CloseHandle(clonedthread);
		return 1;
	}
	processp->remotethread = remotethread;
	return 0;
}

/*
*/

int __stdcall __make_yunoprocess (yunoentrypoint entrypoint, void *parameter, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp, yunoprocess *processp){
	reset_yunoerror();
	HANDLE mutex = CreateMutex(NULL, FALSE, MUTEX_NAME_FOR_YUNOAPI);
	if (mutex == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	switch (WaitForSingleObject(mutex, INFINITE)){
		case WAIT_OBJECT_0:
			break;
		default:
		set_yunoerror(YUNOOS_ERROR);
			return 1;
	}
	int result = make_process(entrypoint, parameter, globalmemoryp, globalsharedmemoryp, processp);
	if (ReleaseMutex(mutex) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	if (CloseHandle(mutex) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	return result;
}
