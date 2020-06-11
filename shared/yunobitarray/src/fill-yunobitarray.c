#include <yuno.h>

static inline int fill_zero (yunosize size, yunosize start, yunobitarray *array){
	yunosize length = yunobitarray_length(array);
	if (start + size < length){
		yunosize index = 0;
		// fill first integer. 
		for (; index < size && YUNOBITARRAY_ELEMENT_BIT_LENGTH - (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH; index++){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] &= 
				~(1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH);
		}
		// fill mid-range integers.
		for (; index + YUNOBITARRAY_ELEMENT_BIT_LENGTH < size; index += YUNOBITARRAY_ELEMENT_BIT_LENGTH){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] = 0;
		}
		// fill last integer.
		for (; index < size; index++){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] &= 
				~(1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH);
		}
		return 0;
	}
	else {
		return 1;
	}
}

static inline int fill_one (yunosize size, yunosize start, yunobitarray *array){
	yunosize length = yunobitarray_length(array);
	if (start + size < length){
		yunosize index = 0;
		// fill first integer.
		for (; index < size && YUNOBITARRAY_ELEMENT_BIT_LENGTH - (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH; index++){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] |= 
				1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		}
		// fill mid-range integers.
		for (; index + YUNOBITARRAY_ELEMENT_BIT_LENGTH < size; index += YUNOBITARRAY_ELEMENT_BIT_LENGTH){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] = YUNOBITARRAY_ELEMENT_MAX;
		}
		// fill last integer.
		for (; index < size; index++){
			array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] |= 
				1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
		}
		return 0;
	}
	else {
		return 1;
	}
}

inline int fill_yunobitarray (int value, yunosize size, yunosize start, yunobitarray *array){
	if (value != 0){
		return fill_one(size, start, array);
	}
	else {
		return fill_zero(size, start, array);
	}
}
