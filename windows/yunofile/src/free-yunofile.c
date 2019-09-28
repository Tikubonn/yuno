#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall free_yunofile (yunofile *file){
	void *array = yunofile_buffer_array(&(file->buffer));
	if (array != NULL){
		free(array);
	}
	free(file);
	return YUNOFILE_SUCCESS;
}
