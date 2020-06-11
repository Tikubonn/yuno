#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall wait_read_yunofile (void *sequence, yunowait_mode waitmode, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_READING){
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
				DWORD readsize;
				if (GetOverlappedResult(file->file, &(file->asyncoverlapped), &readsize, winwaitmode) == 0){
					switch (GetLastError()){
						case ERROR_IO_PENDING: 
							set_yunoerror(YUNOBUSY);
							return 1;
						case ERROR_BROKEN_PIPE:
							file->asyncstatus = YUNOFILE_FREE;
							*readsizep = 0;
							return 0;
						case ERROR_HANDLE_EOF: 
							file->asyncstatus = YUNOFILE_FREE;
							*readsizep = 0;
							return 0;
						default: 
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				else {
					if (set_yunobuffer_end(readsize, &(file->asyncbuffer)) != 0){
						set_yunoerror(YUNOERROR);
						return 1;
					}
					file->asyncstatus = YUNOFILE_FREE;
					read_yunobuffer(sequence, readsize, &(file->asyncbuffer));
					*readsizep = readsize;
					file->asyncseek += readsize;
					return 0;
				}
			}
			else 
			if (file->asyncstatus == YUNOFILE_READ_COMPLETED){
				file->asyncstatus = YUNOFILE_FREE;
				read_yunobuffer(sequence, file->asynccompletedsize, &(file->asyncbuffer));
				*readsizep = file->asynccompletedsize;
				return 0;
			}
			else {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_READ_COMPLETED){
				file->asyncstatus = YUNOFILE_FREE;
				read_yunobuffer(sequence, file->asynccompletedsize, &(file->asyncbuffer));
				*readsizep = file->asynccompletedsize;
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
