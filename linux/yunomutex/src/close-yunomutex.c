#include <yuno.private>

yunomutex_status __yunocall close_yunomutex (yunomutex *mutex){
	if (free_yunoshared_memory(mutex->mutexp, sizeof(pthread_mutex_t)) != YUNOSHARED_MEMORY_SUCCESS){
		return YUNOMUTEX_ERROR;
	}
	return YUNOMUTEX_SUCCESS;
}
