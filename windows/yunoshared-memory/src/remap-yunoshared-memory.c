#include <yuno.private>
#include <windows.h>
#include <stddef.h>

int remap_yunoshared_memory (yunoshared_memory **sharedmemoryp){
	for (yunoshared_memory *memory = *sharedmemoryp; memory != NULL; memory = memory->next){
		void *newaddr = MapViewOfFileEx(memory->handle, FILE_MAP_ALL_ACCESS, 0, 0, memory->size, memory->address);
		if (newaddr == NULL){
			return 1;
		}
		memory->address = newaddr;
		init_yunoallocator(newaddr, memory->seqsize, newaddr + memory->seqsize, memory->mapsize, &(memory->allocator));
	}
	return 0;
}
