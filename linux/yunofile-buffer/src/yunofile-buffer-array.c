#include <yuno.private>

void *yunofile_buffer_array (yunofile_buffer *buffer){
	return buffer->sequence;
}
