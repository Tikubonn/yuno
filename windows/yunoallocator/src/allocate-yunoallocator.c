#include <yuno.private>
#include <stddef.h>
#include <stdbool.h>

/*
	この関数は指定されたサイズの自由に使うことのできるメモリ領域を確保します。
	成功した場合にはこの関数は YUNOALLOCATOR_SUCCESS が返し newaddrp に確保されたメモリ領域の先頭アドレスが保存されます。
	保存されるアドレスの値は必ず YUNOALLOCATOR_ALIGNMENT の整数倍になります。
	yunoallocator に十分なメモリ領域が存在しなかった場合にはこの関数は YUNOALLOCATOR_NOT_ENOUGH_MEMORY を返します。
*/

yunoallocator_status allocate_yunoallocator (size_t size, yunoallocator *allocator, void **newaddrp){
	if (0 < size){
		size_t bsize = ALIGN_FOR_YUNOALLOCATOR(size, YUNOALLOCATOR_ALIGNMENT) / YUNOALLOCATOR_ALIGNMENT;
		bool found;
		size_t bfoundindex;
		if (find_yunoallocator_free_space(bsize, allocator, &found, &bfoundindex) != 0){
			return YUNOALLOCATOR_ERROR;
		}
		if (found == true){
			if (fill_yunobitarray(1, bfoundindex, bsize, &(allocator->bitmap)) != 0){
				return YUNOALLOCATOR_ERROR;
			}
			*newaddrp = allocator->sequence + (bfoundindex * YUNOALLOCATOR_ALIGNMENT);
			return YUNOALLOCATOR_SUCCESS;
		}
		return YUNOALLOCATOR_NOT_ENOUGH_MEMORY;
	}
	return YUNOALLOCATOR_ERROR;
} 
