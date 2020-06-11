#include <yuno.h>

inline void init_yunoallocator (void *sequence, yunosize size, yunobitarray_element *bitarrayseq, yunosize bitarraysize, yunoallocator *allocator){
	allocator->sequence = sequence;
	allocator->size = size;
	init_yunobitarray(bitarrayseq, bitarraysize, &(allocator->bitarray));
}
