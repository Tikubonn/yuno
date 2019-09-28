#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall open_yunostandard_input_manually (void *bufferseq, yunosize buffersize, yunofile *file){
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	if (handle == INVALID_HANDLE_VALUE){
		return YUNOFILE_ERROR;
	}
	if (handle == NULL){
		return YUNOFILE_ERROR;
	}
	init_yunofile(YUNOFILE_WRITABLE, handle, bufferseq, buffersize, file);
	return YUNOFILE_SUCCESS;
}
