#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall tell_yunofile (yunofile *file, yunosize *positionp){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		*positionp = file->asyncseek;
		return YUNOFILE_SUCCESS;
	}
	else {
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		LARGE_INTEGER zero;
		zero.QuadPart = 0;
		LARGE_INTEGER newseek;
		if (SetFilePointerEx(file->file, zero, &newseek, FILE_CURRENT) == 0){
			return YUNOFILE_ERROR;
		}
		*positionp = newseek.QuadPart;
		return YUNOFILE_SUCCESS;
	}
}
