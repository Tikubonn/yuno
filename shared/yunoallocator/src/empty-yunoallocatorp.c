#include <yuno.h>
#include <stdbool.h>

#define BOOLEAN(value) ((value) ? true: false)

inline bool empty_yunoallocatorp (yunoallocator *allocator){
	yunosize foundindex;
	return BOOLEAN(find_yunobitarray(1, 0, &(allocator->bitarray), &foundindex) != 0);
}
