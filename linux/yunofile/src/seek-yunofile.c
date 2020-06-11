#include <yuno.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

static int seek_file (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp){
	reset_yunoerror();
	int linuxwhence;
	switch (whence){
		case YUNOFILE_BEGIN:
			linuxwhence = SEEK_SET;
			break;
		case YUNOFILE_CURRENT:
			linuxwhence = SEEK_CUR;
			break;
		case YUNOFILE_END:
			linuxwhence = SEEK_END;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	off_t offset = lseek(file->filefd, distance, linuxwhence);
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
	*newoffsetp = offset;
	return 0;
}

int seek_yunofile (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_FREE){
				return seek_file(distance, whence, file, newoffsetp);
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				return seek_file(distance, whence, file, newoffsetp);
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
