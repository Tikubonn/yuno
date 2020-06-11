#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static inline int seek_async (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		switch (whence){
			case YUNOFILE_BEGIN: {
				file->asyncseek = distance;
				*newoffsetp = distance;
				return 0;
			}
			case YUNOFILE_CURRENT: {
				yunosize newoffset = file->asyncseek + distance;
				file->asyncseek = newoffset;
				*newoffsetp = newoffset;
				return 0;
			}
			case YUNOFILE_END: {
				LARGE_INTEGER filesize;
				if (GetFileSizeEx(file->file, &filesize) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (filesize.QuadPart + distance < 0){
					set_yunoerror(YUNOARGUMENT_ERROR);
					return 1;
				}
				yunosize newoffset = filesize.QuadPart + distance;
				file->asyncseek = newoffset; 
				*newoffsetp = newoffset;
				return 0;
			}
			default: {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
		}
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

static inline int seek_sync (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		DWORD winwhence;
		switch (whence){
			case YUNOFILE_BEGIN:
				winwhence = FILE_BEGIN;
				break;
			case YUNOFILE_CURRENT:
				winwhence = FILE_CURRENT;
				break;
			case YUNOFILE_END:
				winwhence = FILE_END;
				break;
			default:
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
		}
		LARGE_INTEGER windistance;
		windistance.QuadPart = distance;
		LARGE_INTEGER newseek;
		if (SetFilePointerEx(file->file, windistance, &newseek, winwhence) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		*newoffsetp = newseek.QuadPart;
		return 0;	
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

int __stdcall seek_yunofile (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			return seek_async(distance, whence, file, newoffsetp);
		}
		else {
			return seek_sync(distance, whence, file, newoffsetp);
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
