#include <yuno.private>
#include <windows.h>

yunothread_status __stdcall wait_yunothread (yunothread_wait_mode waitmode, yunothread *thread){
	DWORD wait;
	switch (waitmode){
		case YUNOTHREAD_FOREVER:
			wait = INFINITE;
			break;
		case YUNOTHREAD_NOWAIT:
			wait = 0;
			break;
		default:
			return YUNOTHREAD_ERROR;
	}
	switch (WaitForSingleObject(thread->thread, wait)){
		case WAIT_OBJECT_0:
			return YUNOTHREAD_SUCCESS;
		case WAIT_TIMEOUT:
			return YUNOTHREAD_BUSY;
		default:
			return YUNOTHREAD_ERROR;
	}
}
