#include <yuno.h>
#include <unistd.h>

static int read_async_file (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		if (request_read_yunofile(size, file) != 0){
			return 1;
		}
		if (wait_read_yunofile(sequence, YUNOFOREVER, file, readsizep) != 0){
			return 1;
		}
		return 0;
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

static int read_sync_file (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	ssize_t readsize = read(file->filefd, sequence, size);
	if (readsize == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	*readsizep = readsize;
	return 0;
}

int read_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			return read_async_file(sequence, size, file, readsizep);
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				return read_sync_file(sequence, size, file, readsizep);
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
