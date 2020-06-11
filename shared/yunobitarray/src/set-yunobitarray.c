#include <yuno.h>

static inline int set_zero (yunosize index, yunobitarray *array){
	if (index < array->size * YUNOBITARRAY_ELEMENT_BIT_LENGTH){
		yunosize div = index / YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		yunosize mod = index % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		array->sequence[div] &= ~(1 << mod);
		return 0;
	}
	return 1;
}

static inline int set_one (yunosize index, yunobitarray *array){
	if (index < array->size * YUNOBITARRAY_ELEMENT_BIT_LENGTH){
		yunosize div = index / YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		yunosize mod = index % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		array->sequence[div] |= (1 << mod);
		return 0;
	}
	return 1;
}

inline int set_yunobitarray (int value, yunosize index, yunobitarray *array){
	if (value != 0){
		return set_one(index, array);
	}
	else {
		return set_zero(index, array);
	}
}
