#include <yuno.private>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

static yunoshared_memory *make_yunoshared_memory (size_t size, size_t seqsize, size_t mapsize){
	/*
		brk および sbrk 関数は副作用によって malloc 関数の振る舞いに影響を及ぼす可能性があるため
		素直に malloc 関数を呼び出して領域を確保しています。
	*/
	yunoshared_memory *memory = malloc(sizeof(yunoshared_memory));
	if (memory == NULL){
		return NULL;
	}
	void *newaddr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (newaddr == MAP_FAILED){
		return NULL;
	}
	memory->address = newaddr;
	memory->size = size;
	init_yunoallocator(newaddr, seqsize, newaddr + seqsize, mapsize, &(memory->allocator));
	memory->next = NULL;
	return memory;
}

static long get_page_size (){
	return sysconf(_SC_PAGESIZE);
}

static int extend_yunoshared_memory (size_t requestsize){
	size_t pagesize = get_page_size();
	size_t size;
	size_t seqsize;
	size_t mapsize;
	calculate_yunoallocator_size_by_request(requestsize, pagesize, &size, &seqsize, &mapsize);
	yunoshared_memory *memory = make_yunoshared_memory(size, seqsize, mapsize);
	if (memory == NULL){
		return 1;
	}
	memory->next = global_yunoshared_memory;
	global_yunoshared_memory = memory;
	return 0;
}

typedef struct try_allocate_status {
	TRY_ALLOCATE_SUCCESS,
	TRY_ALLOCATE_ERROR,
	TRY_ALLOCATE_NOT_ENOUGH_MEMORY
} try_allocate_status;

static try_allocate_status try_allocate (size_t size, void **newaddrp){
	for (yunoshared_memory *memory = global_yunoshared_memory; memory != NULL; memory = memory->next){
		void *newaddr;
		switch (allocate_yunoallocator(size, &(memory->allocator), &newaddr)){
			case YUNOALLOCATOR_SUCCESS: 
				*newaddrp = newaddr;
				return TRY_ALLOCATE_SUCCESS;
			case YUNOALLOCATOR_NOT_ENOUGH_MEMORY:
				break;
			default:
				return TRY_ALLOCATE_ERROR;
		}
	}
	return TRY_ALLOCATE_NOT_ENOUGH_MEMORY;
}

void __yunocall *allocate_yunoshared_memory (size_t size){
	void *newaddr;
	switch (try_allocate(size, &newaddr)){
		case TRY_ALLOCATE_SUCCESS: {
			return newaddr;
		}
		case TRY_ALLOCATE_NOT_ENOUGH_MEMORY: {
			if (extend_yunoshared_memory(size) != 0){
				return NULL;
			}
			void *newaddr;
			switch (try_allocate(size, &newaddr)){
				case TRY_ALLOCATE_SUCCESS: {
					return newaddr;
				}
				default: {
					return NULL;
				}
			}
		}
		default: {
			return NULL;
		}
	}
}
