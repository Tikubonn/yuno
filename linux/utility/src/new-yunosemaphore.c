#include <yuno.h>

yunosemaphore *new_yunosemaphore (yunosize maxcount){
	yunosemaphore *semaphore = allocate_yunomemory(sizeof(yunosemaphore));
	if (semaphore == NULL){
		return NULL;
	}
	if (make_yunosemaphore(maxcount, semaphore) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(semaphore, sizeof(yunosemaphore));
		set_yunoerror(lasterror);
		return NULL;
	}
	return semaphore;
}
