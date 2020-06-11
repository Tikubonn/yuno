#include <yuno.h>
#include <unistd.h>

static int write_async_file (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		if (request_write_yunofile(sequence, size, file) != 0){
			return 1;
		}
		if (wait_write_yunofile(YUNOFOREVER, file, wrotesizep)!= 0){
			return 1;
		}
		return 0;
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

static int write_sync_file (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	ssize_t wrotesize = write(file->filefd, sequence, size);
	if (wrotesize == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	*wrotesizep = wrotesize;
	return 0;
}

int write_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			return write_async_file(sequence, size, file, wrotesizep);
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				return write_sync_file(sequence, size, file, wrotesizep);
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
