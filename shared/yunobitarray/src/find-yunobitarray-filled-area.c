#include <yuno.h>
#include <stddef.h>
#include <stdbool.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

static inline bool filled_zerop (yunosize size, yunosize start, yunobitarray *array, yunosize *nextindexp){
	yunosize length = yunobitarray_length(array);
	if (start + size < length){
		yunosize index = 0;
		// check first integer.
		for (; index < size && YUNOBITARRAY_ELEMENT_BIT_LENGTH - (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH; index++){
			if ((array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] & (1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH)) != 0){
				*nextindexp = start + index;
				return false;
			}
		}
		// check mid-range integers.
		for (; index + YUNOBITARRAY_ELEMENT_BIT_LENGTH < size; index += YUNOBITARRAY_ELEMENT_BIT_LENGTH){
			if (array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] != 0){
				*nextindexp = start + index;
				return false;
			}
		}
		// check last integer.
		for (; index < size; index++){
			if ((array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] & (1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH)) != 0){
				*nextindexp = start + index;
				return false;
			}
		}
		return true;
	}
	else {
		*nextindexp = length;
		return false;
	}
}

static inline bool filled_onep (yunosize size, yunosize start, yunobitarray *array, yunosize *nextindexp){
	yunosize length = yunobitarray_length(array);
	if (start + size < length){
		yunosize index = 0;
		// check first integer.
		for (; index < size && YUNOBITARRAY_ELEMENT_BIT_LENGTH - (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH; index++){
			if ((array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] & (1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH)) == 0){
				*nextindexp = start + index;
				return false;
			}
		}
		// check mid-range integers.
		for (; index + YUNOBITARRAY_ELEMENT_BIT_LENGTH < size; index += YUNOBITARRAY_ELEMENT_BIT_LENGTH){
			if (array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] == 0){
				*nextindexp = start + index;
				return false;
			}
		}
		// check last integer.
		for (; index < size; index++){
			if ((array->sequence[(start + index) / YUNOBITARRAY_ELEMENT_BIT_LENGTH] & (1 << (start + index) % YUNOBITARRAY_ELEMENT_BIT_LENGTH)) == 0){
				*nextindexp = start + index;
				return false;
			}
		}
		return true;
	}
	else {
		*nextindexp = length;
		return false;
	}
}

static inline int find_zero (yunosize size, yunosize start, yunobitarray *array, yunosize *foundindexp){
	yunosize length = yunobitarray_length(array);
	for (yunosize index = start; index < length;){
		yunosize foundindex;
		if (find_yunobitarray(0, index, array, &foundindex) != 0){
			break;
		}
		yunosize nextindex;
		if (filled_zerop(size, foundindex, array, &nextindex) == true){
			*foundindexp = foundindex;
			return 0;
		}
		else {
			index = nextindex;
		}
	}
	return 1;
}

static inline int find_one (yunosize size, yunosize start, yunobitarray *array, yunosize *foundindexp){
	yunosize length = yunobitarray_length(array);
	for (yunosize index = start; index < length;){
		yunosize foundindex;
		if (find_yunobitarray(1, index, array, &foundindex) != 0){
			break;
		}
		yunosize nextindex;
		if (filled_onep(size, foundindex, array, &nextindex) == true){
			*foundindexp = foundindex;
			return 0;
		}
		else {
			index = nextindex;
		}
	}
	return 1;
}

int find_yunobitarray_filled_area (int value, yunosize size, yunosize start, yunobitarray *array, yunosize *foundindexp){
	if (value == 0){
		return find_zero(size, start, array, foundindexp);
	}
	else {
		return find_one(size, start, array, foundindexp);
	}
}
