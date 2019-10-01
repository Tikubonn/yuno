#include <yuno.private>
#include <windows.h>

yunofile_status __yunocall get_yunostandard_error_manually (void *bufferseq, yunosize buffersize, yunofile *file){
	HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
	if (handle == INVALID_HANDLE_VALUE){
		return YUNOFILE_ERROR;
	}
	if (handle == NULL){
		return YUNOFILE_ERROR;
	}
	init_yunofile(YUNOFILE_WRITABLE, handle, bufferseq, buffersize, file);
	return YUNOFILE_SUCCESS;
}

