#include <yuno.private>
#include <stddef.h>

#define TOBIT(a) ((a)?1:0)

int set_yunobitarray (int value, size_t index, yunobitarray *array){
	size_t length = yunobitarray_length(array);
	if (index < length){
		array->sequence[index / YUNOBYTE_BIT_COUNT] = 
			array->sequence[index / YUNOBYTE_BIT_COUNT] & ~(1 << (index % YUNOBYTE_BIT_COUNT)) | (TOBIT(value) << (index % YUNOBYTE_BIT_COUNT));
		return 0;
	}
	return 1;
}
