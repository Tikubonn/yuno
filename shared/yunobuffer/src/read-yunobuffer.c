#include <yuno.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

inline yunosize read_yunobuffer (void *sequence, yunosize size, yunobuffer *buffer){
	yunosize readsize = MIN(size, buffer->seekend - buffer->seek);
	for (yunosize index = 0; index < readsize; index++){
		((char*)(sequence))[index] = 
			((char*)(buffer->sequence))[index + buffer->seek];
	}
	buffer->seek = buffer->seek + readsize;
	return readsize;
}
