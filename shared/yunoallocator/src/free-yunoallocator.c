#include <yuno.h>

inline int free_yunoallocator (void *address, yunosize size, yunoallocator *allocator){
	if (yunoallocator_managed_addressp(address, allocator) == true){
		yunosize bitmapsize = SCALE_FOR_YUNOALLOCATOR_BITMAP(size);
		yunosize index = (address - allocator->sequence) / sizeof(max_align_t);
		if (fill_yunobitarray(0, bitmapsize, index, &(allocator->bitarray)) != 0){
			return 1;
		}
		return 0;
	}
	else {
		return 1;
	}
}
