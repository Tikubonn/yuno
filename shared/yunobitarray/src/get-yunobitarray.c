#include <yuno.h>

#define TO_BIT(value) ((value)!=0?1:0)

inline int get_yunobitarray (yunosize index, yunobitarray *array, int *valuep){
	if (index < array->size * YUNOBITARRAY_ELEMENT_BIT_LENGTH){
		yunosize div = index / YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		yunosize mod = index % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		*valuep = TO_BIT(array->sequence[div] & (1 << mod));
		return 0;
	}
	return 1;
}
