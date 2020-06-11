#include <yuno.h>
#include <semaphore.h>

int release_yunosemaphore (yunosemaphore *semaphore){
	reset_yunoerror();
	if (semaphore->closedp == false){
		if (sem_post(semaphore->semaphorep) != 0){
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
