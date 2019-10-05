#include <yuno.private>
#include <sys/mman.h>
#include <stdlib.h>
#include <stddef.h>

static int free_memory (yunoshared_memory *prevmemory, yunoshared_memory *memory){
	if (munmap(memory->address, memory->size) != 0){
		return 1;
	}
	if (memory == global_yunoshared_memory){
		global_yunoshared_memory = memory->next;
	}
	else {
		prevmemory->next = memory->next;
	}
	free(memory);
	return 0;
}

yunoshared_memory_status __yunocall free_yunoshared_memory (void *address, size_t size){
	yunoshared_memory *prevmemory = NULL;
	yunoshared_memory *memory = global_yunoshared_memory;
	while (memory != NULL){
		if (yunoallocator_allocated_memoryp(address, &(memory->allocator)) == true){
			if (free_yunoallocator(address, size, &(memory->allocator)) != YUNOALLOCATOR_SUCCESS){
				return YUNOSHARED_MEMORY_ERROR;
			}
			if (free_yunoallocatorp(&(memory->allocator)) == true){
				if (free_memory(prevmemory, memory) != 0){
					return YUNOSHARED_MEMORY_ERROR;
				}
			}
			return YUNOSHARED_MEMORY_SUCCESS;
		}
		prevmemory = memory;
		memory = memory->next;
	}
	return YUNOSHARED_MEMORY_ERROR;
}
