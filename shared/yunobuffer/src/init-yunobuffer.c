#include <yuno.h>

inline void init_yunobuffer (void *sequence, yunosize size, yunobuffer *buffer){
	buffer->sequence = sequence;
	buffer->seek = 0;
	buffer->seekend = 0;
	buffer->size = size;
}
