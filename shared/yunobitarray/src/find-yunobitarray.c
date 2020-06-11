#include <yuno.h>
#include <stddef.h>

static inline int find_zero (yunosize start, yunobitarray *array, yunosize *foundindexp){
	yunosize startdiv = start / YUNOBITARRAY_ELEMENT_BIT_LENGTH;
	yunosize startmod = start % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
	if (startdiv < array->size){
		if (array->sequence[startdiv] != YUNOBITARRAY_ELEMENT_MAX){
			for (size_t bitindex = startmod; bitindex < YUNOBITARRAY_ELEMENT_BIT_LENGTH; bitindex++){
				if ((array->sequence[startdiv] & (1 << bitindex)) == 0){
					*foundindexp = startdiv * YUNOBITARRAY_ELEMENT_BIT_LENGTH + bitindex;
					return 0;
				}
			}
		}
	}
	for (yunosize index = startdiv +1; index < array->size; index++){
		if (array->sequence[index] != YUNOBITARRAY_ELEMENT_MAX){
			for (size_t bitindex = 0; bitindex < YUNOBITARRAY_ELEMENT_BIT_LENGTH; bitindex++){
				if ((array->sequence[index] & (1 << bitindex)) == 0){
					*foundindexp = index * YUNOBITARRAY_ELEMENT_BIT_LENGTH + bitindex;
					return 0;
				}
			}
		}
	}
	return 1;
}

static inline int find_one (yunosize start, yunobitarray *array, yunosize *foundindexp){
	yunosize startdiv = start / YUNOBITARRAY_ELEMENT_BIT_LENGTH;
	yunosize startmod = start % YUNOBITARRAY_ELEMENT_BIT_LENGTH;
	if (startdiv < array->size){
		if (array->sequence[startdiv] != 0){
			for (size_t bitindex = startmod; bitindex < YUNOBITARRAY_ELEMENT_BIT_LENGTH; bitindex++){
				if ((array->sequence[startdiv] & (1 << bitindex)) != 0){
					*foundindexp = startdiv * YUNOBITARRAY_ELEMENT_BIT_LENGTH + bitindex;
					return 0;
				}
			}
		}
	}
	for (yunosize index = startdiv +1; index < array->size; index++){
		if (array->sequence[index] != 0){
			for (size_t bitindex = 0; bitindex < YUNOBITARRAY_ELEMENT_BIT_LENGTH; bitindex++){
				if ((array->sequence[index] & (1 << bitindex)) != 0){
					*foundindexp = index * YUNOBITARRAY_ELEMENT_BIT_LENGTH + bitindex;
					return 0;
				}
			}
		}
	}
	return 1;
}

int find_yunobitarray (int value, yunosize start, yunobitarray *array, yunosize *foundindexp){
	if (value){
		return find_one(start, array, foundindexp);
	}
	else {
		return find_zero(start, array, foundindexp);
	}
}
