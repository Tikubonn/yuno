#include <yuno.h>

static inline void clear (yunobitarray_element *sequence, yunosize size){
	for (yunosize index = 0; index < size; index++){
		sequence[index] = 0;
	}
}

inline void init_yunobitarray (yunobitarray_element *sequence, yunosize size, yunobitarray *array){
	clear(sequence, size);
	array->sequence = sequence;
	array->size = size;
}
