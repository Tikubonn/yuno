#include <stddef.h>

/*
	実際に要求される領域の大きさを
	ビット配列で記録する際の大きさにスケールダウンします
*/

#define SCALE_FOR_YUNOALLOCATOR_BITMAP(size) (((size) / sizeof(max_align_t)) + (0 < (size) % sizeof(max_align_t) ? 1: 0))

/*
	ビット配列の長さから
	管理対象の領域の大きさを求めます
*/

#define SCALE_FOR_YUNOALLOCATOR(size) ((size) * sizeof(max_align_t) * YUNOBITARRAY_ELEMENT_BIT_LENGTH)

/*
	大きなメモリ領域を管理するデータ型です
	このデータ型は必要に応じてメモリ領域の一部を分配することができます
	このデータ型は管理するメモリ領域とは別に、その領域の使用状況を管理するためのビット配列の領域を要求します
	ビット配列の領域は (管理対象の領域 / (sizeof(max_align_t) * YUNOBITARRAY_ELEMENT_BIT_LENGTH)) 
	以上の大きさである必要があります
*/

typedef struct yunoallocator {
	void *sequence;
	yunosize size;
	yunobitarray bitarray;
} yunoallocator;
