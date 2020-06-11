#include <yuno.h>
#include <sys/mman.h>
#include <stdbool.h>

int sync_yunoshared_memory (void *address){
	reset_yunoerror();
	for (yunoshared_memory *memory = global_yunoshared_memory; memory != NULL; memory = memory->next){
		if (yunoallocator_managed_addressp(address, &(memory->allocator)) == true){
			void *allocatorseq = yunoallocator_array(&(memory->allocator));
			yunosize allocatorsize = yunoallocator_size(&(memory->allocator));
			if (msync(allocatorseq, allocatorsize, MS_SYNC) != 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			return 0;
		}
	}
	set_yunoerror(YUNOARGUMENT_ERROR);
	return 1;
}
