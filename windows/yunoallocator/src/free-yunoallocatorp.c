#include <yuno.private>
#include <stdbool.h>

bool free_yunoallocatorp (yunoallocator *allocator){
	return empty_yunobitarrayp(&(allocator->bitmap));
}
