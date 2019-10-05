#include <yuno.private>
#include <stddef.h>

void init_yunoallocator (void *seq, size_t seqsize, void *mapseq, size_t mapseqsize, yunoallocator *allocator){
	allocator->sequence = seq;
	allocator->size = seqsize;
	init_yunobitarray(mapseq, mapseqsize, &(allocator->bitmap));
}
