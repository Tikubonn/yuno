#include <yuno.h>

inline void *yunoallocator_array (yunoallocator *allocator){
	return allocator->sequence;
}
