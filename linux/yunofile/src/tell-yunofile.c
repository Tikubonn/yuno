#include <yuno.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

static int tell_file (yunofile *file, yunosize *offsetp){
	reset_yunoerror();
	off_t offset = lseek(file->filefd, 0, SEEK_CUR);
	if (offset == -1){
		switch (errno){
			case EINVAL:
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			default:
				set_yunoerror(YUNOOS_ERROR);
				return 1;
		}
	}
	*offsetp = offset;
	return 0;
}

int tell_yunofile (yunofile *file, yunosize *offsetp){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_FREE){
				return tell_file(file, offsetp);
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				return tell_file(file, offsetp);
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
