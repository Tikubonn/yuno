#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall open_async_yunostandard_input_manually (void *bufferseq, yunosize buffersize, yunofile *file){
	HANDLE handle = CreateFile("CONIN$", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (handle == INVALID_HANDLE_VALUE){
		return YUNOFILE_ERROR;
	}
	init_async_yunofile(YUNOFILE_WRITABLE, handle, bufferseq, buffersize, 0, file);
	return YUNOFILE_SUCCESS;
}
