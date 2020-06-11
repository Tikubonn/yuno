#include <yuno.h>

inline void *yunobitarray_array (yunobitarray *array){
	return array->sequence;
}
