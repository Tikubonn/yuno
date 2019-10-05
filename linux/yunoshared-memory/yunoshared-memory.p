#include <stddef.h>

typedef struct yunoshared_memory {
	void *address;
	size_t size;
	yunoallocator allocator;
	struct yunoshared_memory *next;
} yunoshared_memory;
