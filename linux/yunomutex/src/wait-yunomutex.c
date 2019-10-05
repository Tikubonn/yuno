#include <yuno.private>
#include <pthread.h>
#include <errno.h>

yunomutex_status __yunocall wait_yunomutex (yunomutex_wait_mode waitmode, yunomutex *mutex){
	switch (waitmode){
		case YUNOMUTEX_FOREVER: {
			if (pthread_mutex_lock(mutex->mutexp) != 0){
				return YUNOMUTEX_ERROR;
			}
			return YUNOMUTEX_SUCCESS;
		}
		case YUNOMUTEX_NOWAIT: {
			if (pthread_mutex_trylock(mutex->mutexp) != 0){
				switch (errno){
					case EBUSY: 
						return YUNOMUTEX_BUSY;
					default:
						return YUNOMUTEX_ERROR;
				}
			}
			return YUNOMUTEX_SUCCESS;
		}
		default: {
			return YUNOMUTEX_ERROR; // unknown wait mode!
		}
	}
}
