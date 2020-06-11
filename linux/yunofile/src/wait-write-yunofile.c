#include <yuno.h>
#include <poll.h>
#include <unistd.h>

static int wait_write_async_file (yunowait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	int timeout;
	switch (waitmode){
		case YUNOFOREVER:
			timeout = -1;
			break;
		case YUNONOWAIT:
			timeout = 0;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	struct pollfd pfd;
	pfd.fd = file->filefd;
	pfd.events = POLLOUT;
	pfd.revents = 0;
	int pollresult = poll(&pfd, 1, timeout);
	if (pollresult == 1){
		void *bufferseq = yunobuffer_array(&(file->asyncbuffer));
		ssize_t wrotesize = write(file->filefd, bufferseq, file->asynccompletedsize);
		if (wrotesize == -1){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		file->asyncstatus = YUNOFILE_FREE;
		*wrotesizep = wrotesize;
		return 0;
	}
	else 
	if (pollresult == 0){
		set_yunoerror(YUNOBUSY);
		return 1;
	}
	else {
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
}

static int wait_write_sync_file (yunowait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	(void)waitmode; // ignore unused warning!
	reset_yunoerror();
	void *bufferseq = yunobuffer_array(&(file->asyncbuffer));
	ssize_t wrotesize = write(file->filefd, bufferseq, file->asynccompletedsize);
	if (wrotesize == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	file->asyncstatus = YUNOFILE_FREE;
	*wrotesizep = wrotesize;
	return 0;
}

int wait_write_yunofile (yunowait_mode waitmode, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_WRITING){
				return wait_write_async_file(waitmode, file, wrotesizep);
			}
			else 
			if (file->asyncstatus == YUNOFILE_FREE){
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_WRITING){
				return wait_write_sync_file(waitmode, file, wrotesizep);
			}
			else 
			if (file->asyncstatus == YUNOFILE_FREE){
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
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
