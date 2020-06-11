#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static inline DWORD get_page_size (){
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	return systeminfo.dwPageSize;
}

static inline void setup_security_attributes (SECURITY_ATTRIBUTES *secattrs){
	secattrs->nLength = sizeof(SECURITY_ATTRIBUTES);
	secattrs->lpSecurityDescriptor = NULL;
	secattrs->bInheritHandle = TRUE;
}

#define MIN_OFFSET 0x20000
//#define MAX_OFFSET 0x7fffffff
#define MAX_OFFSET 0x6fffffff

static inline void *prepare_area (yunosize size){
	reset_yunoerror();
	for (void *baseaddr = (void*)MAX_OFFSET; (void*)MIN_OFFSET < baseaddr;){
		MEMORY_BASIC_INFORMATION meminfo;
		if (0 < VirtualQuery(baseaddr, &meminfo, sizeof(meminfo))){
			if (meminfo.State == MEM_FREE && size <= meminfo.RegionSize){
				void *reserved = VirtualAlloc(meminfo.BaseAddress, size, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
				if (reserved == NULL){
					baseaddr = meminfo.BaseAddress != (void*)0 ? meminfo.BaseAddress -1: (void*)0;
					continue;
				}
				if (VirtualFree(reserved, 0, MEM_RELEASE) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return NULL;
				}
				return reserved;
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

static inline yunoshared_memory *make_yunoshared_memory (yunosize size, yunoshared_memory *nextmemory, yunomemory **globalmemoryp){
	reset_yunoerror();
	DWORD pagesize = get_page_size();
	yunosize pageresolution = SCALE_FOR_YUNOALLOCATOR(pagesize);
	yunosize bitarraysize = ((size / pageresolution) + (0 < size % pageresolution ? 1: 0)) * pagesize;
	yunosize allocatorsize = SCALE_FOR_YUNOALLOCATOR(bitarraysize);
	SECURITY_ATTRIBUTES secattrs;
	setup_security_attributes(&secattrs);
	ULARGE_INTEGER mappingsize;
	mappingsize.QuadPart = bitarraysize + allocatorsize;
	HANDLE mappingfile = CreateFileMapping(INVALID_HANDLE_VALUE, &secattrs, PAGE_EXECUTE_READWRITE | SEC_COMMIT, mappingsize.HighPart, mappingsize.LowPart, NULL);
	if (mappingfile == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	void *prepared = prepare_area(mappingsize.QuadPart);
	if (prepared == NULL){
		return NULL;
	}
	void *mappedaddress = MapViewOfFileEx(mappingfile, FILE_MAP_ALL_ACCESS, 0, 0, 0, prepared);
	if (mappedaddress == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	yunoshared_memory *newmemory = __allocate_yunomemory(sizeof(yunoshared_memory), globalmemoryp);
	if (newmemory == NULL){
		return NULL;
	}
	DWORD currentprocessid = GetCurrentProcessId();
	init_yunoshared_memory(
		currentprocessid, 
		mappingfile, 
		mappedaddress, 
		allocatorsize, 
		mappedaddress + allocatorsize, 
		bitarraysize, 
		mappedaddress, 
		bitarraysize + allocatorsize, 
		nextmemory, 
		newmemory
	);
	return newmemory;
}

static inline void *doallocate (yunosize size, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp){
	reset_yunoerror();
	DWORD currentprocessid = GetCurrentProcessId();
	for (yunoshared_memory *memory = *globalsharedmemoryp; memory != NULL; memory = memory->next){
		if (memory->processid == currentprocessid){
			void *allocated = allocate_yunoallocator(size, &(memory->allocator));
			if (allocated != NULL){
				return allocated;
			}
		}
	}
	yunoshared_memory *newmemory = make_yunoshared_memory(size, *globalsharedmemoryp, globalmemoryp);
	if (newmemory == NULL){
		return NULL;
	}
	*globalsharedmemoryp = newmemory;
	void *allocated = allocate_yunoallocator(size, &(newmemory->allocator));
	if (allocated == NULL){
		//set_yunoerror(YUNONOT_ENOUGH_MEMORY);
		set_yunoerror(YUNOERROR);
		return NULL;
	}
	return allocated;
}

void *__stdcall __allocate_yunoshared_memory (yunosize size, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp){
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
	void *allocated = doallocate(size, globalmemoryp, globalsharedmemoryp);
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
