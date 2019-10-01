#include <yuno.private>
#include <windows.h>

yunomutex_status __yunocall wait_yunomutex (yunomutex_wait_mode waitmode, yunomutex *mutex){
	DWORD wait;
	switch (waitmode){
		case YUNOMUTEX_FOREVER:
			wait = INFINITE;
			break;
		case YUNOMUTEX_NOWAIT:
			wait = 0;
			break;
		default:
			return YUNOMUTEX_ERROR;
	}
	switch (WaitForSingleObject(mutex->mutex, wait)){
		case WAIT_OBJECT_0: 
			return YUNOFILE_SUCCESS;
		case WAIT_TIMEOUT:
			return YUNOFILE_BUSY;
		default:
			return YUNOFILE_ERROR;
	}
}
