#include <yuno.h>
#include <stdbool.h>

int close_yunomutex (yunomutex *mutex){
	reset_yunoerror();
	if (mutex->closedp == false){
		if (free_yunoshared_memory(mutex->mutexp, sizeof(pthread_mutex_t)) != 0){
			return 1;
		}
		mutex->closedp = true;
		return 0;
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
