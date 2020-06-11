#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static inline int free_memory (void *address, yunosize size){
	reset_yunoerror();
	if (VirtualFree(address, size, MEM_DECOMMIT) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	if (VirtualFree(address, 0, MEM_RELEASE) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	return 0;
}

static inline int dofree (void *address, yunosize size, yunomemory **memoryp){
	reset_yunoerror();
	yunomemory **nextmemoryp;
	yunomemory *memory;
	for (nextmemoryp = memoryp, memory = *memoryp; memory != NULL; nextmemoryp = &(memory->next), memory = memory->next){
		if (yunoallocator_managed_addressp(address, &(memory->allocator)) == true){
			if (free_yunoallocator(address, size, &(memory->allocator)) != 0){
				return 1;
			}
			if (empty_yunoallocatorp(&(memory->allocator)) == true){
				*nextmemoryp = memory->next;
				if (free_memory(memory->bitarrayseq, memory->bitarraysize) != 0){
					return 1;
				}
				if (free_memory(memory->sequence, memory->size) != 0){
					return 1;
				}
			}
			return 0;
		}
	}
	return 1;
}

int __stdcall __free_yunomemory (void *address, yunosize size, yunomemory **memoryp){
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
	int result = dofree(address, size, memoryp);
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
