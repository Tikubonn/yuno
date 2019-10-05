#include <yuno.private>
#include <pthread.h>

yunomutex_status __yunocall make_yunomutex_manually (yunomutex *mutex){
	pthread_mutex_t *mutexp = allocate_yunoshared_memory(sizeof(pthread_mutex_t));
	if (mutexp == NULL){
		return YUNOMUTEX_ERROR;
	}
	*mutexp = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(mutexp, NULL);
	mutex->mutexp = mutexp;
	return YUNOMUTEX_SUCCESS;
}
