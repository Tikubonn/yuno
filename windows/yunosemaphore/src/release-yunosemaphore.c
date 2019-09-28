#include <yuno.private>
#include <windows.h>

yunosemaphore_status __stdcall release_yunosemaphore (yunosemaphore *semaphore){
	LONG prevcount;
	if (ReleaseSemaphore(semaphore->semaphore, 1, &prevcount) == 0){
		return YUNOSEMAPHORE_ERROR;
	}
	return YUNOSEMAPHORE_SUCCESS;
}
