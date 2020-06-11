#include <yuno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

static int try_wait (yunowait_mode waitmode, yunoprocess *process){
	int option;
	switch (waitmode){
		case YUNOFOREVER:
			option = 0;
			break;
		case YUNONOWAIT:
			option = WNOHANG;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	int status;
	int waitted = waitpid(process->processid, &status, option);
	if (waitted == process->processid){
		if (WIFEXITED(status)){
			process->exitedp = true;
			process->exitcode = WEXITSTATUS(status);
			return 0;
		}
		else {
			set_yunoerror(YUNOERROR);
			return 1;
		}
	}
	else 
	if (waitted == 0){
		set_yunoerror(YUNOBUSY);
		return 1;
	}
	else {
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
}

int wait_yunoprocess (yunowait_mode waitmode, yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		if (process->exitedp == false){
			if (process->processid != getpid()){
				return try_wait(waitmode, process);
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
