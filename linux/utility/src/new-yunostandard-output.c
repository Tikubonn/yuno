#include <yuno.h>
#include <stdbool.h>

yunofile *new_yunostandard_output (bool asyncp, yunosize buffersize){
	void *buffer = allocate_yunomemory(buffersize);
	if (buffer == NULL){
		return NULL;
	}
	yunofile *file = allocate_yunomemory(sizeof(yunofile));
	if (file == NULL){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(buffer, buffersize);
		set_yunoerror(lasterror);
		return NULL;
	}
	if (open_yunostandard_error(asyncp, buffer, buffersize, file) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(buffer, buffersize);
		free_yunomemory(file, sizeof(yunofile));
		set_yunoerror(lasterror);
		return NULL;
	}
	return file;
}
