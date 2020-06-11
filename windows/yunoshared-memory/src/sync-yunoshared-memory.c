#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall __sync_yunoshared_memory (void *address, yunoshared_memory **memoryp){
	reset_yunoerror();
	for (yunoshared_memory *memory = *memoryp; memory != NULL; memory = memory->next){
		if (yunoallocator_managed_addressp(address, &(memory->allocator)) == true){
			void *allocatorseq = yunoallocator_array(&(memory->allocator));
			if (FlushViewOfFile(allocatorseq, 0) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			return 0;
		}
	}
	set_yunoerror(YUNOARGUMENT_ERROR);
	return 1;
}
