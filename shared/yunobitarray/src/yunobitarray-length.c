#include <yuno.h>

inline yunosize yunobitarray_length (yunobitarray *array){
	return array->size * YUNOBITARRAY_ELEMENT_BIT_LENGTH;
}
