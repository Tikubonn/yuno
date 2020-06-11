#include <yuno.h>
#include <sys/types.h>
#include <unistd.h>

int get_yunothread_exit_code (yunothread *thread, int *exitcodep){
	reset_yunoerror();
	if (thread->closedp == false){
		if (thread->exitedp == true){
			if (thread->thread != pthread_self()){
				*exitcodep = thread->exitcode;
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
