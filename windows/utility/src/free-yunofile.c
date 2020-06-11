#include <yuno.h>
#include <windows.h>

int __stdcall __free_yunofile (yunofile *file, yunomemory **globalmemoryp){
	void *bufferseq = yunofile_buffer_array(file);
	yunosize buffersize = yunofile_buffer_size(file);
	if (__free_yunomemory(bufferseq, buffersize, globalmemoryp) != 0){
		return 1;
	}
	if (__free_yunomemory(file, sizeof(yunofile), globalmemoryp) != 0){
		return 1;
	}
	return 0;
}
