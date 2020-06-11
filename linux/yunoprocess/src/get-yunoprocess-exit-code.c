#include <yuno.h>
#include <unistd.h>

int get_yunoprocess_exit_code (yunoprocess *process, int *exitcodep){
	reset_yunoerror();
	if (process->closedp == false){
		if (process->exitedp == true){
			if (process->processid != getpid()){
				*exitcodep = process->exitcode;
				return 0;
			}
			else {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
		}
		else {
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
