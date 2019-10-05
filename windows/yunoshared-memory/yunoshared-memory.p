#include <windows.h>
#include <stddef.h>

typedef struct yunoshared_memory {
	HANDLE handle;
	void *address;
	size_t size;
	size_t seqsize;
	size_t mapsize;
	yunoallocator allocator;
	struct yunoshared_memory *next;
} yunoshared_memory;
