#include <yuno.private>
#include <stddef.h>

yunosize yunofile_buffer_max_size (yunofile_buffer *buffer){
	return buffer->size;
}
