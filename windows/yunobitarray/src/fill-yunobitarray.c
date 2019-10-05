#include <yuno.private>
#include <stddef.h>

int fill_yunobitarray (int value, size_t offset, size_t size, yunobitarray *array){
	size_t length = yunobitarray_length(array);
	if (offset + size < length){
		for (size_t index = 0; index < size; index++){
			if (set_yunobitarray(value, offset + index, array) != 0){
				return 1;
			}
		}
		return 0;
	}
	return 1;
}
