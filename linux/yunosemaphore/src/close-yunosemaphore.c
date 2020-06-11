#include <yuno.h>
#include <stdbool.h>

int close_yunosemaphore (yunosemaphore *semaphore){
	reset_yunoerror();
	if (semaphore->closedp == false){
		if (free_yunoshared_memory(semaphore->semaphorep, sizeof(sem_t)) != 0){
			return 1;
		}
		semaphore->closedp = true;
		return 0;
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
