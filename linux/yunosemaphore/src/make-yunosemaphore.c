#include <yuno.private>
#include <stdlib.h>

yunosemaphore __yunocall *make_yunosemaphore (){
	yunosemaphore *semaphore = malloc(sizeof(yunosemaphore));
	if (semaphore == NULL){
		return NULL;
	}
	if (make_yunosemaphore_manually(semaphore) != YUNOMUTEX_SUCCESS){
		free(semaphore);
		return NULL;
	}
	return semaphore;
}
