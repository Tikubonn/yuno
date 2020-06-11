#include <yuno.h>

static int request_read_async_file (yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->asyncstatus == YUNOFILE_FREE){
		file->asynccompletedsize = size;
		file->asyncstatus = YUNOFILE_READING;
		return 0;
	}
	else {
		set_yunoerror(YUNOBUSY);
		return 1;
	}
}

static int request_read_sync_file (yunosize size, yunofile *file){
	reset_yunoerror();
	file->asynccompletedsize = size;
	file->asyncstatus = YUNOFILE_READING;
	return 0;
}

int request_read_yunofile (yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			return request_read_async_file(size, file);
		}
		else {
			return request_read_sync_file(size, file);
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
