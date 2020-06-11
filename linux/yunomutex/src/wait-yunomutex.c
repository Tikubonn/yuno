#include <yuno.h>
#include <pthread.h>
#include <errno.h>

int wait_yunomutex (yunowait_mode waitmode, yunomutex *mutex){
	reset_yunoerror();
	if (mutex->closedp == false){
		switch (waitmode){
			case YUNOFOREVER: {
				if (pthread_mutex_lock(mutex->mutexp) != 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				return 0;
			}
			case YUNONOWAIT: {
				if (pthread_mutex_trylock(mutex->mutexp) != 0){
					switch (errno){
						case EBUSY:
							set_yunoerror(YUNOBUSY);
							return 1;
						default:
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				return 0;
			}
			default: {
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1; 
			}
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
