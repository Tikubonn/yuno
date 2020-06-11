#include <yuno.h>
#include <semaphore.h>

int make_yunosemaphore (yunosize maxcount, yunosemaphore *semaphore){
	reset_yunoerror();
	if (0 < maxcount){
		sem_t *semaphorep = allocate_yunoshared_memory(sizeof(sem_t));
		if (semaphorep == NULL){
			return 1;
		}
		sem_init(semaphorep, 1, maxcount);
		semaphore->semaphorep = semaphorep;
		semaphore->closedp = false;
		return 0;
	}
	else {
		set_yunoerror(YUNOARGUMENT_ERROR);
		return 1;
	}
}
