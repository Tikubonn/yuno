#include <yuno.private>
#include <semaphore.h>

yunosemaphore_status __yunocall release_yunosemaphore (yunosemaphore *semaphore){
	if (sem_post(semaphore->semaphorep) != 0){
		return YUNOSEMAPHORE_ERROR;
	}
	return YUNOSEMAPHORE_SUCCESS;
}
