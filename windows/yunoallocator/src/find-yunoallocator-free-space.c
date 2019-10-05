#include <yuno.private>
#include <stddef.h>
#include <stdbool.h>

static int check_space (size_t boffset, size_t bsize, yunoallocator *allocator, bool *foundp, size_t *bnextindexp){
	size_t blength = yunobitarray_length(&(allocator->bitmap));
	if (boffset + bsize < blength){
		for (size_t bindex = 0; bindex < bsize; bindex++){
			int value;
			if (get_yunobitarray(boffset + bindex, &(allocator->bitmap), &value) != 0){
				return 1;
			}
			if (value){
				*foundp = false;
				*bnextindexp = boffset + bindex +1;
				return 0;
			}
		}
		*foundp = true;
		return 0;
	}
	*foundp = false;
	*bnextindexp = blength;
	return 0;
}

int find_yunoallocator_free_space (size_t bsize, yunoallocator *allocator, bool *foundp, size_t *bfoundindexp){
	size_t blength = yunobitarray_length(&(allocator->bitmap));
	size_t bindex = 0;
	while (bindex < blength){
		bool found;
		size_t bnextindex;
		if (check_space(bindex, bsize, allocator, &found, &bnextindex) != 0){
			return 1;
		}
		if (found == true){
			*foundp = true;
			*bfoundindexp = bindex;
			return 0;
		}
		bindex = bnextindex;
	}
	*foundp = false;
	return 0;
}
