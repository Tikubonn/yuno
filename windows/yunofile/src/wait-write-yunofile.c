#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall wait_write_yunofile (yunowait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_WRITING){
				BOOL winwaitmode;
				switch (waitmode){
					case YUNOFOREVER: 
						winwaitmode = TRUE;
						break;
					case YUNONOWAIT:
						winwaitmode = FALSE;
						break;
					default:
						set_yunoerror(YUNOARGUMENT_ERROR);
						return 1;
				}
				switch (WaitForSingleObject(file->event, winwaitmode)){
					case WAIT_OBJECT_0: 
						break;
					case WAIT_TIMEOUT: 
						set_yunoerror(YUNOBUSY);
						return 1;
					default: 
						set_yunoerror(YUNOOS_ERROR);
						return 1;
				}
				DWORD wrotesize;
				if (GetOverlappedResult(file->file, &(file->asyncoverlapped), &wrotesize, winwaitmode) == 0){
					switch (GetLastError()){
						case ERROR_IO_PENDING: 
							set_yunoerror(YUNOBUSY);
							return 1;
						default: 
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				else {
					file->asyncstatus = YUNOFILE_FREE;
					file->asyncseek += wrotesize;
					*wrotesizep = wrotesize;
					return 0;
				}
			}
			else 
			if (file->asyncstatus == YUNOFILE_WRITE_COMPLETED){
				file->asyncstatus = YUNOFILE_FREE;
				*wrotesizep = file->asynccompletedsize;
				return 0;
			}
			else {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_WRITE_COMPLETED){
				file->asyncstatus = YUNOFILE_FREE;
				*wrotesizep = file->asynccompletedsize;
				return 0;
			}
			else {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
