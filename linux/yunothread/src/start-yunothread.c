#include <yuno.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int start_yunothread (yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		if (thread->exitedp == false){
			if (thread->thread != pthread_self()){
			  if (pthread_kill(thread->thread, SIGCONT) != 0){
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
