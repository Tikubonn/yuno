#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall close_yunofile (yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncstatus == YUNOFILE_FREE){
			if (CloseHandle(file->file) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1; 
			}
			if (file->event != NULL){
				if (CloseHandle(file->event) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1; 
				}
			}
			file->closedp = true;
			return 0;
		}
		else {
			set_yunoerror(YUNOBUSY);
			return 1;
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
