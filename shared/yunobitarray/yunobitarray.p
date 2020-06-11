#include <stdint.h>

/*
	yunobitarray_element 型のすべてのビットが 1 の場合の値です
*/

#define YUNOBITARRAY_ELEMENT_MAX UINT8_MAX 

/*
	yunobitarray_element 型のビット幅です
*/

#define YUNOBITARRAY_ELEMENT_BIT_LENGTH 8

/*
	yunobitarray の要素となる符号なし整数型です
*/

typedef uint8_t yunobitarray_element;

/*
	ビット配列を管理するデータ型です
	この型は確保されたメモリ領域を管理する yunoallocator 型で使用されます
*/

typedef struct yunobitarray {
	yunobitarray_element *sequence;
	yunosize size;
} yunobitarray;
