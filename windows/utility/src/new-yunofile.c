#include <yuno.h>
#include <windows.h>

yunofile *__stdcall __new_yunofile (const char *filename, int mode, yunosize buffersize, yunomemory **globalmemoryp){
	yunofile *file = __allocate_yunomemory(sizeof(yunofile), globalmemoryp);
	if (file == NULL){
		return NULL;
	}
	void *buffer = __allocate_yunomemory(buffersize, globalmemoryp);
	if (buffer == NULL){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(file, sizeof(yunofile), globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	if (open_yunofile(filename, mode, buffer, buffersize, file) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(file, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(buffer, buffersize, globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return file;
}
