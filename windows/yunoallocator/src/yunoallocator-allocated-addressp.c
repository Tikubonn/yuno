#include <yuno.private>
#include <stdbool.h>

bool yunoallocator_allocated_addressp (void *address, yunoallocator *allocator){
	return 
		allocator->sequence <= address && 
		address < allocator->sequence + allocator->size;
}
