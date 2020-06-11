#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

yunofile *__stdcall __new_yunostandard_output (bool asyncp, yunosize buffersize, yunomemory **globalmemoryp){
	reset_yunoerror();
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
	if (open_yunostandard_output(asyncp, buffer, buffersize, file) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(file, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(buffer, buffersize, globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return file;
}
