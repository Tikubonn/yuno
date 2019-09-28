#include <yuno.private>
#include <stdlib.h>

yunosemaphore __stdcall *make_yunosemaphore (int maxcount){
	yunosemaphore *semaphore = malloc(sizeof(yunosemaphore));
	if (semaphore == NULL){
		return NULL;
	}
	if (make_yunosemaphore_manually(maxcount, semaphore) != YUNOMUTEX_SUCCESS){
		free(semaphore);
		return NULL;
	}
	return semaphore;
}
