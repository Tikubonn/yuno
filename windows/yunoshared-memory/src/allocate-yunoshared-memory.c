#include <yuno.private>
#include <windows.h>
#include <stddef.h>
//#include <stdio.h>//test

static yunoshared_memory *make_yunoshared_memory (size_t size, size_t seqsize, size_t mapsize){
	HANDLE heap = GetProcessHeap();
	if (heap == NULL){
		return NULL;
	}
	//printf("heap=%d\n", heap);//test
	yunoshared_memory *memory = HeapAlloc(heap, 0, sizeof(yunoshared_memory));
	if (memory == NULL){
		return NULL;
	}
	//printf("memory=%p\n", memory);//test
	SECURITY_ATTRIBUTES secattr;
	secattr.nLength = sizeof(secattr);
	secattr.lpSecurityDescriptor = NULL;
	secattr.bInheritHandle = TRUE;
	LARGE_INTEGER memsize;
	memsize.QuadPart = seqsize + mapsize;
	HANDLE filemap = CreateFileMapping(INVALID_HANDLE_VALUE, &secattr, PAGE_READWRITE, memsize.HighPart, memsize.LowPart, NULL);
	if (filemap == NULL){
		if (HeapFree(heap, 0, memory) == 0){
			return NULL;
		}
		return NULL;
	}
	void *sequence = MapViewOfFile(filemap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (sequence == NULL){
		if (CloseHandle(filemap) == 0){
			return NULL;
		}
		if (HeapFree(heap, 0, memory) == 0){
			return NULL;
		}
		return NULL;
	}
	memory->handle = filemap;
	memory->address = sequence;
	memory->size = size;
	memory->seqsize = seqsize;
	memory->mapsize = mapsize;
	init_yunoallocator(sequence, seqsize, sequence + seqsize, mapsize, &(memory->allocator));
	memory->next = NULL;
	return memory;
}

static DWORD get_page_size (){
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	return systeminfo.dwPageSize;
}

static int extend_yunoshared_memory (size_t reqsize, yunoshared_memory **sharedmemoryp){
	size_t size;
	size_t seqsize;
	size_t mapsize;
	DWORD pagesize = get_page_size();
	calculate_yunoallocator_size_by_request(reqsize, pagesize, &size, &seqsize, &mapsize);
	yunoshared_memory *memory = make_yunoshared_memory(size, seqsize, mapsize);
	if (memory == NULL){
		return 1;
	}
	memory->next = *sharedmemoryp;
	*sharedmemoryp = memory;
	return 0;
}

typedef enum try_allocate_status {
	TRY_ALLOCATE_SUCCESS,
	TRY_ALLOCATE_ERROR,
	TRY_ALLOCATE_NOT_ENOUGH_MEMORY
} try_allocate_status;

static int try_allocate (size_t size, yunoshared_memory **sharedmemoryp, void **newaddrp){
	for (yunoshared_memory *memory = *sharedmemoryp; memory != NULL; memory = memory->next){
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

void __yunocall *__allocate_yunoshared_memory (size_t size, yunoshared_memory **sharedmemoryp){
	void *newaddr;
	switch (try_allocate(size, sharedmemoryp, &newaddr)){
		case TRY_ALLOCATE_SUCCESS: {
			return newaddr;
		}
		case TRY_ALLOCATE_NOT_ENOUGH_MEMORY: {
			if (extend_yunoshared_memory(size, sharedmemoryp) != 0){
				return NULL;
			}
			void *newaddr;
			switch (try_allocate(size, sharedmemoryp, &newaddr)){
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
