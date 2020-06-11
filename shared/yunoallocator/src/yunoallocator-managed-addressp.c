#include <yuno.h>
#include <stdbool.h>

inline bool yunoallocator_managed_addressp (void *address, yunoallocator *allocator){
	return allocator->sequence <= address && address < allocator->sequence + allocator->size;
}
