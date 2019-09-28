#include <yuno.private>
#include <stddef.h>

void init_yunofile_buffer (void *sequence, yunosize size, yunofile_buffer *buffer){
	buffer->sequence = sequence;
	buffer->size = size;
	buffer->seek = 0;
}
