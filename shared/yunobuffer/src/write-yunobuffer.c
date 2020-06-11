#include <yuno.h>

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)<(b)?(b):(a))

inline yunosize write_yunobuffer (void *sequence, yunosize size, yunobuffer *buffer){
	yunosize writesize = MIN(size, buffer->size - buffer->seek);
	for (yunosize index = 0; index < writesize; index++){
		((char*)(buffer->sequence))[index + buffer->seek] = 
			((char*)(sequence))[index];
	}
	yunosize newseek = buffer->seek + writesize;
	buffer->seek = newseek;
	buffer->seekend = MAX(newseek, buffer->seekend);
	return writesize;
}
