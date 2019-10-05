#include <stdint.h>
#include <stddef.h>

#define YUNOBYTE_BIT_COUNT 8

typedef uint8_t yunobyte; // must be over 8bits.

typedef struct yunobitarray {
	yunobyte *sequence;
	size_t size;
} yunobitarray;
