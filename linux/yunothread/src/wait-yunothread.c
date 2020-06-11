#define _GNU_SOURCE
#include <yuno.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

static int try_wait (yunowait_mode waitmode, yunothread *thread){
	switch (waitmode){
		case YUNOFOREVER: {
			void *returnedvalue;
			switch (pthread_join(thread->thread, &returnedvalue)){
				case 0:
					thread->exitedp = true;
					thread->exitcode = (int)returnedvalue;
					return 0;
				default:
					set_yunoerror(YUNOOS_ERROR);
					return 1;
			}
		}
		case YUNONOWAIT: {
			void *returnedvalue;
			switch (pthread_tryjoin_np(thread->thread, &returnedvalue)){
				case 0:
					thread->exitedp = true;
					thread->exitcode = (int)returnedvalue;
					return 0;
				case EBUSY:
					set_yunoerror(YUNOBUSY);
					return 1;
				default:
					set_yunoerror(YUNOOS_ERROR);
					return 1;
			}
		}
		default: {
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
		}
	}
}

int wait_yunothread (yunowait_mode waitmode, yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		if (thread->exitedp == false){
			if (thread->thread != pthread_self()){
				return try_wait(waitmode, thread);
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
