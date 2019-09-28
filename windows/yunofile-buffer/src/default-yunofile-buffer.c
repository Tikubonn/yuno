#include <yuno.private>
#include <stddef.h>

void default_yunofile_buffer (yunofile_buffer *buffer){
	buffer->sequence = NULL;
	buffer->size = 0;
	buffer->seek = 0;
}
