#include <yuno.h>

static int request_write_async_file (void *sequence, yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		clear_yunobuffer(&(file->asyncbuffer));
		yunosize wrotesize = write_yunobuffer(sequence, size, &(file->asyncbuffer));
		file->asyncstatus = YUNOFILE_WRITING;
		file->asynccompletedsize = wrotesize;
		return 0;
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

static int request_write_sync_file (void *sequence, yunosize size, yunofile *file){
	reset_yunoerror();
	clear_yunobuffer(&(file->asyncbuffer));
	yunosize wrotesize = write_yunobuffer(sequence, size, &(file->asyncbuffer));
	file->asyncstatus = YUNOFILE_WRITING;
	file->asynccompletedsize = wrotesize;
	return 0;
}

int request_write_yunofile (void *sequence, yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			return request_write_async_file(sequence, size, file);
		}
		else {
			return request_write_sync_file(sequence, size, file);
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
