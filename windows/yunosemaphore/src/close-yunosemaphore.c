#include <yuno.private>
#include <windows.h>

yunosemaphore_status __stdcall close_yunosemaphore (yunosemaphore *semaphore){
	if (CloseHandle(semaphore->semaphore) == 0){
		return YUNOSEMAPHORE_ERROR;
	}
	return YUNOSEMAPHORE_SUCCESS;
}
