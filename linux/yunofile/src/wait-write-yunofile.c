#include <yuno.private>
#include <time.h>
#include <aio.h>
#include <errno.h>

yunofile_status __yunocall wait_write_yunofile (yunofile_wait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_WRITING){ 
			return YUNOFILE_ERROR;
		} 
		struct timespec time;
		struct timespec *timep;
		switch (waitmode){
			case YUNOFILE_FOREVER:
				timep = NULL;
				break;
			case YUNOFILE_NOWAIT:
				time.tv_sec = 0;
				time.tv_nsec = 0;
				timep = &time;
				break;
			default: 
				return YUNOFILE_ERROR;
		}
		struct aiocb const *cbs[] = { &(file->cb) };
		if (aio_suspend(cbs, 1, timep) == -1){ 
			switch (errno){
				case EAGAIN:
					return YUNOFILE_BUSY;
				default:
					return YUNOFILE_ERROR;
			}
		}
		switch (aio_error(&(file->cb))){ 
			case 0: {
				ssize_t wrotesize = aio_return(&(file->cb));
				if (wrotesize < 0){
					return YUNOFILE_ERROR;
				}
				file->requeststatus = YUNOFILE_FREE;
				file->asyncseek += wrotesize;
				*wrotesizep = wrotesize;
				return YUNOFILE_SUCCESS; 
			}
			case EINPROGRESS: {
				return YUNOFILE_BUSY; 
			} 
			default: {
				return YUNOFILE_ERROR; 
			}
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

