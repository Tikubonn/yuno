#include <yuno.h>
#include <sys/mman.h>
#include <unistd.h>

#define DEFAULT_PROTOCOL (PROT_EXEC | PROT_READ | PROT_WRITE)
#define DEFAULT_FLAGS (MAP_SHARED | MAP_ANONYMOUS)

static yunoshared_memory *make_yunoshared_memory (yunosize size, yunoshared_memory *nextmemory){
	reset_yunoerror();
	int pagesize = getpagesize();
	yunosize pageresolution = SCALE_FOR_YUNOALLOCATOR(pagesize);
	yunosize bitarraysize = ((size / pageresolution) + (0 < size % pageresolution ? 1: 0)) * pagesize;
	yunosize allocatorsize = SCALE_FOR_YUNOALLOCATOR(bitarraysize);
	void *bitarrayseq = mmap(NULL, bitarraysize, DEFAULT_PROTOCOL, DEFAULT_FLAGS, -1, 0);
	if (bitarrayseq == MAP_FAILED){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	void *allocatorseq = mmap(NULL, allocatorsize, DEFAULT_PROTOCOL, DEFAULT_FLAGS, -1, 0);
	if (allocatorseq == MAP_FAILED){
		set_yunoerror(YUNOOS_ERROR);
		munmap(bitarrayseq, bitarraysize);
		return NULL;
	}
	yunoshared_memory *memory = allocate_yunomemory(sizeof(yunoshared_memory));
	if (memory == NULL){
		set_yunoerror(YUNOOS_ERROR);
		munmap(bitarrayseq, bitarraysize);
		munmap(allocatorseq, allocatorsize);
		return NULL;
	}
	init_yunoshared_memory(
		allocatorseq,
		allocatorsize,
		bitarrayseq,
		bitarraysize,
		nextmemory,
		memory
	);
	return memory;
}

void *allocate_yunoshared_memory (yunosize size){
	reset_yunoerror();
	for (yunoshared_memory *memory = global_yunoshared_memory; memory != NULL; memory = memory->next){
		void *allocated = allocate_yunoallocator(size, &(memory->allocator));
		if (allocated != NULL){
			return allocated;
		}
	}
	yunoshared_memory *newmemory = make_yunoshared_memory(size, global_yunoshared_memory);
	if (newmemory == NULL){
		return NULL;
	}
	global_yunoshared_memory = newmemory;
	void *allocated = allocate_yunoallocator(size, &(newmemory->allocator));
	if (allocated == NULL){
		//set_yunoerror(YUNONOT_ENOUGH_MEMORY);
		set_yunoerror(YUNOERROR);
		return NULL;
	}
	return allocated;
}
