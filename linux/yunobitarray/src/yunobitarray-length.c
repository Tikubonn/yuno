#include <yuno.private>
#include <stddef.h>

size_t yunobitarray_length (yunobitarray *array){
	return array->size * YUNOBYTE_BIT_COUNT;
}
