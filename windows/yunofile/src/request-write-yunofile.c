#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall request_write_yunofile (void *sequence, yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncstatus == YUNOFILE_FREE){
			if (file->asyncp == true){
				clear_yunobuffer(&(file->asyncbuffer));
				yunosize wrotesize = write_yunobuffer(sequence, size, &(file->asyncbuffer));
				void *wrotearray = yunobuffer_array(&(file->asyncbuffer));
				setup_yunofile_overlapped(file->asyncseek, file->event, &(file->asyncoverlapped));
				DWORD dummy;
				if (WriteFile(file->file, wrotearray, wrotesize, &dummy, &(file->asyncoverlapped)) == 0){
					switch (GetLastError()){
						case ERROR_BROKEN_PIPE:
							file->asyncstatus = YUNOFILE_WRITE_COMPLETED;
							file->asynccompletedsize = 0;
							return 0;
						case ERROR_IO_PENDING: 
							file->asyncstatus = YUNOFILE_WRITING;
							return 0;
						default:
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				switch (file->type){
					case TYPE_YUNOSERVER_PIPE:
						file->asyncstatus = YUNOFILE_WRITING;
						return 0;
					case TYPE_YUNOCLIENT_PIPE:
						file->asyncstatus = YUNOFILE_WRITING;
						return 0;
					default:
						set_yunoerror(YUNOERROR);
						return 1;
				}
			}
			else {
				DWORD wrotesize;
				if (WriteFile(file->file, sequence, size, &wrotesize, NULL) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				file->asyncstatus = YUNOFILE_WRITE_COMPLETED;
				file->asynccompletedsize = wrotesize;
				return 0;
			}
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
