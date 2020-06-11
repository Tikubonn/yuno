#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static int dofree (void *address, yunosize size, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp){
	reset_yunoerror();
	DWORD currentprocessid = GetCurrentProcessId();
	yunoshared_memory **nextmemoryp;
	yunoshared_memory *memory;
	for (nextmemoryp = globalsharedmemoryp, memory = *globalsharedmemoryp; memory != NULL; nextmemoryp = &(memory->next), memory = memory->next){
		if (memory->processid == currentprocessid && 
				yunoallocator_managed_addressp(address, &(memory->allocator)) == true){
			if (free_yunoallocator(address, size, &(memory->allocator)) != 0){
				return 1;
			}
			if (empty_yunoallocatorp(&(memory->allocator)) == true){
				*nextmemoryp = memory->next;
				if (UnmapViewOfFile(memory->mappingaddress) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (CloseHandle(memory->mappingfile) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (__free_yunomemory(memory, sizeof(yunoshared_memory), globalmemoryp) != 0){
					return 1;
				}
			}
			return 0;
		}
	}
	set_yunoerror(YUNOERROR);
	return 1;
}

int __stdcall __free_yunoshared_memory (void *address, yunosize size, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp){
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
	int result = dofree(address, size, globalmemoryp, globalsharedmemoryp);
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
