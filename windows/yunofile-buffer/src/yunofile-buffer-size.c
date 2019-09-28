#include <yuno.private>
#include <stddef.h>

yunosize yunofile_buffer_size (yunofile_buffer *buffer){
	return buffer->seek;
}
