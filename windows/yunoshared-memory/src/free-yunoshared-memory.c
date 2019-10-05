#include <yuno.private>
#include <windows.h>
#include <stdbool.h>
//#include <stdio.h>//test

static int __free_memory (yunoshared_memory *prevmemory, yunoshared_memory *memory, yunoshared_memory **sharedmemoryp){
	if (UnmapViewOfFile(memory->address) == 0){
		return 1;
	}
	if (CloseHandle(memory->handle) == 0){
		return 1;
	}
	yunoshared_memory *next = memory->next;
	/*
		HeapFree がセグ違反するため原因の特定が終わるまで一時的にコメントアウトしています。
		していました。再コンパイルしているうちに解決したようです。
		おそらくは中間ファイルが古かったために HeapFree ではなく不定なアドレスを呼出していたようです。
	*/
	HANDLE heap = GetProcessHeap();
	if (heap == NULL){
		return 1;
	}
	//printf("heap=%d\n", heap);//test
	//printf("memory=%p\n", memory);//test
	if (HeapFree(heap, 0, memory) == 0){
		return 1;
	}
	if (memory == *sharedmemoryp){
		*sharedmemoryp = next;
		return 0;
	}
	else {
		prevmemory->next = next;
		return 0;
	}
}

yunoshared_memory_status __yunocall __free_yunoshared_memory (void *address, size_t size, yunoshared_memory **sharedmemoryp){
	yunoshared_memory *memory = *sharedmemoryp;
	yunoshared_memory *prevmemory = NULL;
	while (memory != NULL){
		if (yunoallocator_allocated_addressp(address, &(memory->allocator)) == true){
			if (free_yunoallocator(address, size, &(memory->allocator)) != 0){
				return YUNOSHARED_MEMORY_ERROR;
			}
			if (free_yunoallocatorp(&(memory->allocator)) == true){
				if (__free_memory(prevmemory, memory, sharedmemoryp) != 0){
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
