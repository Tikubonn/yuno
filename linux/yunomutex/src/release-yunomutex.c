#include <yuno.private>
#include <pthread.h>

yunomutex_status __yunocall release_yunomutex (yunomutex *mutex){
	if (pthread_mutex_unlock(mutex->mutexp) != 0){
		return YUNOMUTEX_ERROR;
	}
	return YUNOMUTEX_SUCCESS;
}
