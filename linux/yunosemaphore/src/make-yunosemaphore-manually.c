#include <yuno.private>
#include <semaphore.h>

yunosemaphore_status __yunocall make_yunosemaphore_manually (int maxcount, yunosemaphore *semaphore){
	if (0 < maxcount){
		sem_t *semaphorep = allocate_yunoshared_memory(sizeof(sem_t));
		if (semaphorep == NULL){
			return YUNOSEMAPHORE_ERROR;
		}
		sem_init(semaphorep, 1, maxcount); // share by other processes.
		semaphore->semaphorep = semaphorep;
		return YUNOSEMAPHORE_SUCCESS;
	}
	return YUNOSEMAPHORE_ERROR;
}
