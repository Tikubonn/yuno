#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall seek_yunofile (yunossize seek, yunofile_where where, yunofile *file, yunosize *newseekp){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		switch (where){
			case YUNOFILE_BEGIN: {
				if (seek < 0){
					return YUNOFILE_ERROR;
				}
				file->asyncseek = seek;
				return YUNOFILE_SUCCESS;
			}
			case YUNOFILE_CURRENT: {
				if (file->asyncseek + seek < 0){
					return YUNOFILE_ERROR;
				}
				file->asyncseek = file->asyncseek + seek;
				return YUNOFILE_SUCCESS;
			}
			case YUNOFILE_END: {
				LARGE_INTEGER filesize;
				if (GetFileSizeEx(file->file, &filesize) == 0){
					return YUNOFILE_SUCCESS;
				}
				if (filesize.QuadPart + seek < 0){
					return YUNOFILE_ERROR;
				}
				file->asyncseek = filesize.QuadPart + seek;
				return YUNOFILE_SUCCESS;
			}
			default: {
				return YUNOFILE_ERROR;
			}
		}
	}
	else {
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		DWORD whe;
		switch (where){
			case YUNOFILE_BEGIN:
				whe = FILE_BEGIN;
				break;
			case YUNOFILE_CURRENT:
				whe = FILE_CURRENT;
				break;
			case YUNOFILE_END:
				whe = FILE_END;
				break;
			default:
				return YUNOFILE_ERROR;
		}
		LARGE_INTEGER se;
		se.QuadPart = seek;
		LARGE_INTEGER newseek;
		if (SetFilePointerEx(file->file, se, &newseek, whe) == 0){
			return YUNOFILE_ERROR;
		}
		*newseekp = newseek.QuadPart;
		return YUNOFILE_SUCCESS;
	}
}
