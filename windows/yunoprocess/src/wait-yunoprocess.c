#include <yuno.private>
#include <windows.h>

yunoprocess_status __yunocall wait_yunoprocess (yunoprocess_wait_mode waitmode, yunoprocess *process){
	DWORD wait;
	switch (waitmode){
		case YUNOPROCESS_FOREVER:
			wait = INFINITE;
			break;
		case YUNOPROCESS_NOWAIT:
			wait = 0;
			break;
		default:
			return YUNOPROCESS_ERROR;
	}
	switch (WaitForSingleObject(process->process, wait)){
		case WAIT_OBJECT_0:
			return YUNOPROCESS_SUCCESS;
		case WAIT_TIMEOUT:
			return YUNOPROCESS_BUSY;
		default:
			return YUNOPROCESS_ERROR;
	}
}
