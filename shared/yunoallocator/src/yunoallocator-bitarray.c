#include <yuno.h>

inline yunobitarray *yunoallocator_bitarray (yunoallocator *allocator){
	return &(allocator->bitarray);
}
