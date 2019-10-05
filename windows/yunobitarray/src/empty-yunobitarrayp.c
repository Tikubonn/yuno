#include <yuno.private>
#include <stdbool.h>

bool empty_yunobitarrayp (yunobitarray *bitarray){
	for (size_t index = 0; index < bitarray->size; index++){
		if (bitarray->sequence[index] != 0){
			return false;
		}
	}
	return true;
}
