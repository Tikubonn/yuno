#include <yuno.private>
#include <stddef.h>
#include <stdio.h>//test

#define TOBIT(a) ((a)?1:0)

int get_yunobitarray (size_t index, yunobitarray *array, int *valuep){
	size_t length = yunobitarray_length(array);
	if (index < length){
		*valuep = TOBIT(array->sequence[index / YUNOBYTE_BIT_COUNT] & (1 << (index % YUNOBYTE_BIT_COUNT)));
		return 0;
	}
	return 1;
}
