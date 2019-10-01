#include <yuno.private>
#include <windows.h>
#include <stdio.h>

yunosemaphore_status __yunocall wait_yunosemaphore (yunosemaphore_wait_mode waitmode, yunosemaphore *semaphore){
	DWORD wait;
	switch (waitmode){
		case YUNOSEMAPHORE_FOREVER:
			wait = INFINITE;
			break;
		case YUNOSEMAPHORE_NOWAIT:
			wait = 0;
			break;
		default:
			return YUNOSEMAPHORE_ERROR;
	}
	switch (WaitForSingleObject(semaphore->semaphore, wait)){
		case WAIT_OBJECT_0:
			return YUNOSEMAPHORE_SUCCESS;
		case WAIT_TIMEOUT:
			return YUNOSEMAPHORE_BUSY;
		default:
			return YUNOSEMAPHORE_ERROR;
	}
}
