#include <yuno.private>
#include <stddef.h>
#define MYMIN(a,b) ((a)<(b)?(a):(b))

yunosize map_yunofile_buffer (void *source, yunosize size, yunofile_buffer *buffer){
	yunosize si = MYMIN(size, buffer->size);
	for (yunosize index = 0; index < si; index++){
		((char*)(buffer->sequence))[index] = 
			((char*)source)[index];
	}
	buffer->seek = si;
	return si;
}
