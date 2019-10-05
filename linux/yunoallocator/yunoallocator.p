#include <stdint.h>
#include <stddef.h>

#define YUNOALLOCATOR_ALIGNMENT sizeof(intmax_t)

typedef enum yunoallocator_status {
	YUNOALLOCATOR_SUCCESS,
	YUNOALLOCATOR_ERROR,
	YUNOALLOCATOR_NOT_ENOUGH_MEMORY
} yunoallocator_status;

typedef struct yunoallocator {
	yunobitarray bitmap;
	void *sequence;
	size_t size;
} yunoallocator;

/*
	offset を base の整数倍に調節するマクロです。
	yunoallocator の多くの関数で使用するのでマクロ化しています。
*/

#define ALIGN_FOR_YUNOALLOCATOR(offset, base)\
((offset) % (base) == 0 ? (offset) : ((offset) + (base) - (offset) % (base)))
