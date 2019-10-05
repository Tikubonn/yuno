#include <yuno.private>
#include <pthread.h>

yunomutex_status __yunocall make_yunomutex_manually (yunomutex *mutex){
  pthread_mutexattr_t mutattr;
  pthread_mutexattr_init(&mutattr);
  if (pthread_mutexattr_setpshared(&mutattr, PTHREAD_PROCESS_SHARED) != 0){
    return YUNOMUTEX_ERROR;
  }
  pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
  //pthread_mutex_init(&mut, NULL);
  pthread_mutex_init(&mut, &mutattr);
	pthread_mutex_t *mutp = allocate_yunoshared_memory(sizeof(pthread_mutex_t));
	if (mutp == NULL){
		return YUNOMUTEX_ERROR;
	}
  *mutp = mut;
	mutex->mutexp = mutp;
	return YUNOMUTEX_SUCCESS;
}

