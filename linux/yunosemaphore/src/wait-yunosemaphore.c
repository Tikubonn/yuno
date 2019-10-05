#include <yuno.private>
#include <semaphore.h>
#include <errno.h>

yunosemaphore_status __yunocall wait_yunosemaphore (yunosemaphore_wait_mode waitmode, yunosemaphore *semaphore){
	switch (waitmode){
		case YUNOSEMAPHORE_FOREVER: 
			if (sem_wait(semaphore->semaphorep) != 0){
				return YUNOSEMAPHORE_ERROR; 
			}
			return YUNOSEMAPHORE_SUCCESS;
		case YUNOSEMAPHORE_NOWAIT: 
			if (sem_trywait(semaphore->semaphorep) != 0){
				switch (errno){
					case EAGAIN:
						return YUNOSEMAPHORE_BUSY;
					default:
						return YUNOSEMAPHORE_ERROR;
				}
			}
			return YUNOSEMAPHORE_SUCCESS;
		default:
			return YUNOSEMAPHORE_ERROR;
	}
}
