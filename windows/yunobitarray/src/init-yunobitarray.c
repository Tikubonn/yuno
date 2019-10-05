#include <yuno.private>
#include <stddef.h>

void init_yunobitarray (yunobyte *sequence, size_t size, yunobitarray *array){
	array->sequence = sequence;
	array->size = size;
}
