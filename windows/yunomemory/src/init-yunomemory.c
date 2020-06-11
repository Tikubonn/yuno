#include <yuno.h>

inline void init_yunomemory (
	void *sequence,
	yunosize size,
	void *allocatorseq,
	yunosize allocatorsize,
	yunobitarray_element *bitarrayseq,
	yunosize bitarraysize,
	yunomemory *nextmemory,
	yunomemory *memory){
	memory->sequence = sequence;
	memory->size = size;
	memory->allocatorseq = allocatorseq;
	memory->allocatorsize = allocatorsize;
	memory->bitarrayseq = bitarrayseq;
	memory->bitarraysize = bitarraysize;
	init_yunoallocator(
		allocatorseq,
		allocatorsize,
		bitarrayseq,
		bitarraysize,
		&(memory->allocator)
	);
	memory->next = nextmemory;
}
