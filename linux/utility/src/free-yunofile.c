#include <yuno.h>

int free_yunofile (yunofile *file){
	void *bufferseq = yunofile_buffer_array(file);
	yunosize buffersize = yunofile_buffer_size(file);
	if (free_yunomemory(bufferseq, buffersize) != 0){
		return 1;
	}
	if (free_yunomemory(file, sizeof(yunofile)) != 0){
		return 1;
	}
	return 0;
}
