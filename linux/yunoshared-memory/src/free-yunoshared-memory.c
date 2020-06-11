#include <yuno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

int free_yunoshared_memory (void *address, yunosize size){
	reset_yunoerror();
	yunoshared_memory **nextmemoryp;
	yunoshared_memory *memory;
	for (nextmemoryp = &global_yunoshared_memory, memory = global_yunoshared_memory; memory != NULL; nextmemoryp = &(memory->next), memory = memory->next){
		if (yunoallocator_managed_addressp(address, &(memory->allocator)) == true){
			if (free_yunoallocator(address, size, &(memory->allocator)) != 0){
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
			if (empty_yunoallocatorp(&(memory->allocator)) == true){
				*nextmemoryp = memory->next;
				if (munmap(memory->bitarrayseq, memory->bitarraysize) != 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (munmap(memory->allocatorseq, memory->allocatorsize) != 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (free_yunomemory(memory, sizeof(yunoshared_memory)) != 0){
					return 1;
				}
			}
			return 0;
		}
	}
	set_yunoerror(YUNOARGUMENT_ERROR);
	return 1;
}
