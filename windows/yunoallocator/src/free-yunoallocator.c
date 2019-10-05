#include <yuno.private>
#include <stddef.h>
#include <stdbool.h>

/*
	この関数は allocate_yunoallocator で確保されたメモリ領域を yunoallocator に返還します。
	address の値は allocate_yunoallocator で返されたアドレスでなければなりません。
	size の値は allocate_yunoallocator で要求したサイズでなければなりません。
	それ以外の値を与えた場合のこの関数の挙動は未定義です。
	この関数は成功した場合には YUNOALLOCATOR_SUCCESS を返します。
	それ以外の場合には YUNOALLOCATOR_ERROR を返します。
*/

yunoallocator_status free_yunoallocator (void *address, size_t size, yunoallocator *allocator){
	if (yunoallocator_allocated_addressp(address, allocator) == true){
		size_t boffset = (address - allocator->sequence) / YUNOALLOCATOR_ALIGNMENT;
		size_t bsize = ALIGN_FOR_YUNOALLOCATOR(size, YUNOALLOCATOR_ALIGNMENT) / YUNOALLOCATOR_ALIGNMENT;
		if (fill_yunobitarray(0, boffset, bsize, &(allocator->bitmap)) != 0){
			return YUNOALLOCATOR_ERROR;
		}
		return YUNOALLOCATOR_SUCCESS;
	}
	return YUNOALLOCATOR_ERROR;
}
