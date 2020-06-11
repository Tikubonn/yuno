#include <yuno.h>
#include <windows.h>

int __stdcall __free_yunosemaphore (yunosemaphore *semaphore, yunomemory **globalmemoryp){
	return __free_yunomemory(semaphore, sizeof(yunosemaphore), globalmemoryp);
}
