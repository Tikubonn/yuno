#include <yuno.h>
#include <windows.h>

yunosemaphore *__stdcall __new_yunosemaphore (yunosize maxcount, yunomemory **globalmemoryp){
	yunosemaphore *semaphore = __allocate_yunomemory(sizeof(yunosemaphore), globalmemoryp);
	if (semaphore == NULL){
		return NULL;
	}
	if (make_yunosemaphore(maxcount, semaphore) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(semaphore, sizeof(yunosemaphore), globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return semaphore;
}
