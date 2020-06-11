#include <yuno.h>
#include <unistd.h>
#include <stdbool.h>

static int close_file (yunofile *file){
	reset_yunoerror();
	if (close(file->filefd) == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	file->closedp = true;
	return 0;
}

int close_yunofile (yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_FREE){
				return close_file(file);
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_FREE){
				return close_file(file);
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
