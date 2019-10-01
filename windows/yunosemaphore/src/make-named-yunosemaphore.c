#include <yuno.private>
#include <stdlib.h>

yunosemaphore __yunocall *make_named_yunosemaphore (const char *name, int maxcount){
	yunosemaphore *semaphore = malloc(sizeof(yunosemaphore));
	if (semaphore == NULL){
		return NULL;
	}
	if (make_named_yunosemaphore_manually(name, maxcount, semaphore) != YUNOMUTEX_SUCCESS){
		free(semaphore);
		return NULL;
	}
	return semaphore;
}
