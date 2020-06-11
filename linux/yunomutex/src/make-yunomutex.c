#include <yuno.h>
#include <pthread.h>

int make_yunomutex (yunomutex *mutex){
  reset_yunoerror();
  pthread_mutexattr_t mutattr;
  pthread_mutexattr_init(&mutattr);
  if (pthread_mutexattr_setpshared(&mutattr, PTHREAD_PROCESS_SHARED) != 0){
    set_yunoerror(YUNOOS_ERROR);
    return 1;
  }
  pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
  //pthread_mutex_init(&mut, NULL);
  pthread_mutex_init(&mut, &mutattr);
	pthread_mutex_t *mutexp = allocate_yunoshared_memory(sizeof(pthread_mutex_t));
	if (mutexp == NULL){
		return 1;
	}
  *mutexp = mut;
	mutex->mutexp = mutexp;
  mutex->closedp = false;
	return 0;
}
