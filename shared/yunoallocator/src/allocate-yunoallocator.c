#include <yuno.h>

inline void *allocate_yunoallocator (yunosize size, yunoallocator *allocator){
	yunosize bitmapsize = SCALE_FOR_YUNOALLOCATOR_BITMAP(size);
	yunosize foundindex;
	if (find_yunobitarray_filled_area(0, bitmapsize, 0, &(allocator->bitarray), &foundindex) != 0){
		return NULL;
	}
	if (fill_yunobitarray(1, bitmapsize, foundindex, &(allocator->bitarray)) != 0){
		return NULL;
	}
	return allocator->sequence + foundindex * sizeof(max_align_t);
}
