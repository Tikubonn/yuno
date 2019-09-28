#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall close_yunofile (yunofile *file){
	if (file->requeststatus != YUNOFILE_FREE){
		return YUNOFILE_BUSY;
	}
	if (CloseHandle(file->file) == 0){
		return YUNOFILE_ERROR;
	}
	return YUNOFILE_SUCCESS;
}
