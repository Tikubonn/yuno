#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall tell_yunofile (yunofile *file, yunosize *offsetp){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_FREE){
				*offsetp = file->asyncseek;
				return 0;
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				LARGE_INTEGER zero;
				zero.QuadPart = 0;
				LARGE_INTEGER newseek;
				if (SetFilePointerEx(file->file, zero, &newseek, FILE_CURRENT) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				*offsetp = newseek.QuadPart;
				return 0;
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
