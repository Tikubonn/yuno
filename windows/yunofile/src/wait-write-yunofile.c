#include <yuno.private>
#include <windows.h>

yunofile_status __yunocall wait_write_yunofile (yunofile_wait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_WRITING){
			return YUNOFILE_ERROR;
		}
		BOOL wait;
		switch (waitmode){
			case YUNOFILE_FOREVER:
				wait = TRUE;
				break;
			case YUNOFILE_NOWAIT:
				wait = FALSE;
				break;
			default:
				return YUNOFILE_ERROR;
		}
		DWORD wrotesize;
		if (GetOverlappedResult(file->file, &(file->overlapped), &wrotesize, wait) == 0){
			switch (GetLastError()){
				case ERROR_IO_PENDING: 
					return YUNOFILE_BUSY; // now busy!
				default: 
					return YUNOFILE_ERROR;
			}
		}
		else {
			file->requeststatus = YUNOFILE_FREE;
			file->asyncseek += wrotesize;
			*wrotesizep = wrotesize;
			return YUNOFILE_SUCCESS;
		}
	}
	else {
		if (file->requeststatus != YUNOFILE_WRITE_COMPLETED){
			return YUNOFILE_ERROR;
		}
		file->requeststatus = YUNOFILE_FREE;
		*wrotesizep = file->completedsize;
		return YUNOFILE_SUCCESS;
	}
}
