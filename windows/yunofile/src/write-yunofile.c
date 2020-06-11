#include <yuno.h>
#include <windows.h>

int __stdcall write_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncstatus == YUNOFILE_FREE){
			if (file->asyncp == true){
				if (request_write_yunofile(sequence, size, file) != 0){
					return 1;
				}
				if (wait_write_yunofile(YUNOFOREVER, file, wrotesizep) != 0){
					return 1;
				}
				return 0;
			}
			else {
				DWORD wrotesize;
				if (WriteFile(file->file, sequence, size, &wrotesize, NULL) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				*wrotesizep = wrotesize;
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
