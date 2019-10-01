#include <stddef.h>

typedef struct yunofile_buffer {
	char *sequence;
	yunosize size;
	yunosize seek;
} yunofile_buffer;
