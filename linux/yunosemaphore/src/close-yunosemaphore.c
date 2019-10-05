#include <yuno.private>
#include <semaphore.h>

yunosemaphore_status __yunocall close_yunosemaphore (yunosemaphore *semaphore){
	if (free_yunoshared_memory(semaphore->semaphorep, sizeof(sem_t)) != YUNOSEMAPHORE_SUCCESS){
		return YUNOSEMAPHORE_ERROR;
	}
	return YUNOSEMAPHORE_SUCCESS;
}
