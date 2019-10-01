#include <yuno.private>
#include <windows.h>

yunofile_status __yunocall get_async_yunostandard_output_manually (void *bufferseq, yunosize buffersize, yunofile *file){
	HANDLE handle = CreateFile("CONOUT$", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (handle == INVALID_HANDLE_VALUE){
		return YUNOFILE_ERROR;
	}
	init_async_yunofile(YUNOFILE_WRITABLE, handle, bufferseq, buffersize, 0, file);
	return YUNOFILE_SUCCESS;
}
