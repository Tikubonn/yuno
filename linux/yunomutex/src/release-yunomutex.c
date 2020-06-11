#include <yuno.h>
#include <pthread.h>

int release_yunomutex (yunomutex *mutex){
	reset_yunoerror();
	if (mutex->closedp == false){
		if (pthread_mutex_unlock(mutex->mutexp) != 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		return 0;
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
