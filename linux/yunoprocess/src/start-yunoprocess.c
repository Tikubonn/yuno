#include <yuno.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int start_yunoprocess (yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		if (process->exitedp == false){
			if (process->processid != getpid()){
				if (kill(process->processid, SIGCONT) != 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
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
