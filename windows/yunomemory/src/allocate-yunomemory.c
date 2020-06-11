#include <yuno.h>
#include <windows.h>
#include <stddef.h>
#include <stdbool.h>

#define MIN_OFFSET 0x20000
//#define MAX_OFFSET 0x7fffffff
#define MAX_OFFSET 0x6fffffff

/*
	要求された大きさを持つ領域を、プロセスのメモリ領域から確保します
	この関数は前方からではなく後方から利用可能な領域を検索します
*/

static inline void *allocate_memory (yunosize size){
	reset_yunoerror();
	for (void *baseaddr = (void*)MAX_OFFSET; (void*)MIN_OFFSET < baseaddr;){
		MEMORY_BASIC_INFORMATION meminfo;
		if (0 < VirtualQuery(baseaddr, &meminfo, sizeof(meminfo))){
			if ((void*)MIN_OFFSET < baseaddr && meminfo.State == MEM_FREE && size <= meminfo.RegionSize){
				void *reserved = VirtualAlloc(meminfo.BaseAddress, size, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
				if (reserved != NULL){
					void *committed = VirtualAlloc(reserved, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
					if (committed != NULL){
						return committed;
					}
					set_yunoerror(YUNOOS_ERROR);
					return NULL;
				}
			}
			baseaddr = meminfo.BaseAddress != (void*)0 ? meminfo.BaseAddress -1: (void*)0;
		}
		else {
			DWORD lasterror = GetLastError();
			if (lasterror == ERROR_INVALID_PARAMETER){
				break;
			}
			else {
				set_yunoerror(YUNOOS_ERROR);
				return NULL;
			}
		}
	}
	set_yunoerror(YUNONOT_ENOUGH_MEMORY);
	return NULL;
}

/*
	確保された領域を解放します
	この関数は複数の領域の確保に失敗した際に
	確保済みの領域を解放するために使われます
	そのためこの関数は実行結果の成否にかかわらず 
	thread_yunoerror の状態を変更しません
*/

static inline int free_memory (void *address, yunosize size){
	if (VirtualFree(address, size, MEM_DECOMMIT) == 0){
		return 1;
	}
	if (VirtualFree(address, 0, MEM_RELEASE) == 0){
		return 1;
	}
	return 0;
}

static inline DWORD get_page_size (){
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	return systeminfo.dwPageSize;
}

#define MAX(a, b) ((a)<(b)?(b):(a))

static inline yunomemory *make_yunomemory (yunosize size, yunomemory *nextmemory){
	DWORD pagesize = get_page_size();
	void *bitarrayseq;
	yunosize bitarraysize;
	{
		yunosize pageresolution = SCALE_FOR_YUNOALLOCATOR(pagesize);
		bitarraysize = ((size / pageresolution) + (0 < size % pageresolution ? 1: 0)) * pagesize;
		bitarrayseq = allocate_memory(bitarraysize);
		if (bitarrayseq == NULL){
			return NULL;
		}
	}
	void *memoryseq;
	yunosize memorysize;
	{
		yunosize requiresize = 
			YUNOALIGN(sizeof(yunomemory), sizeof(max_align_t)) + 
			YUNOALIGN(size, sizeof(max_align_t));
		memorysize = MAX(
			SCALE_FOR_YUNOALLOCATOR(bitarraysize),
			((requiresize / pagesize) + (0 < requiresize % pagesize ? 1: 0)) * pagesize
		);
		memoryseq = allocate_memory(memorysize);
		if (memoryseq == NULL){
			free_memory(bitarrayseq, bitarraysize);
			return NULL;
		}
	}
	yunomemory *newmemory = memoryseq;
	init_yunomemory(
		memoryseq,
		memorysize,
		memoryseq + YUNOALIGN(sizeof(yunomemory), sizeof(max_align_t)),
		memorysize - YUNOALIGN(sizeof(yunomemory), sizeof(max_align_t)),
		bitarrayseq,
		bitarraysize,
		nextmemory,
		newmemory
	);
	return newmemory;
}

static inline void *doallocate (yunosize size, yunomemory **memoryp){
	reset_yunoerror();
	for (yunomemory *memory = *memoryp; memory != NULL; memory = memory->next){
		void *allocated = allocate_yunoallocator(size, &(memory->allocator));
		if (allocated != NULL){
			return allocated;
		}
	}
	yunomemory *newmemory = make_yunomemory(size, *memoryp);
	if (newmemory == NULL){
		return NULL;
	}
	*memoryp = newmemory;
	void *allocated = allocate_yunoallocator(size, &(newmemory->allocator));
	if (allocated == NULL){
		//set_yunoerror(YUNONOT_ENOUGH_MEMORY);
		set_yunoerror(YUNOERROR);
		return NULL;
	}
	return allocated;
}

void *__stdcall __allocate_yunomemory (yunosize size, yunomemory **memoryp){
	reset_yunoerror();
	HANDLE mutex = CreateMutex(NULL, FALSE, MUTEX_NAME_FOR_YUNOAPI);
	if (mutex == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	switch (WaitForSingleObject(mutex, INFINITE)){
		case WAIT_OBJECT_0:
			break;
		default:
			set_yunoerror(YUNOOS_ERROR);
			return NULL;
	}
	void *allocated = doallocate(size, memoryp);
	if (ReleaseMutex(mutex) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	if (CloseHandle(mutex) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	return allocated;
}
