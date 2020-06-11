#include <yuno.h>

inline void init_yunoshared_memory (void *allocatorseq, yunosize allocatorsize, void *bitarrayseq, yunosize bitarraysize, yunoshared_memory *nextmemory, yunoshared_memory *memory){
	memory->allocatorseq = allocatorseq;
	memory->allocatorsize = allocatorsize;
	memory->bitarrayseq = bitarrayseq;
	memory->bitarraysize = bitarraysize;
	init_yunoallocator(allocatorseq, allocatorsize, bitarrayseq, bitarraysize, &(memory->allocator));
	memory->next = nextmemory;
}
