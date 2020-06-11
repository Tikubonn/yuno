#include <yuno.h>
#include <windows.h>

int __stdcall wait_yunomutex (yunowait_mode waitmode, yunomutex *mutex){
	reset_yunoerror();
	DWORD winwaitmode;
	switch (waitmode){
		case YUNONOWAIT:
			winwaitmode = 0;
			break;
		case YUNOFOREVER:
			winwaitmode = INFINITE;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	switch (WaitForSingleObject(mutex->mutex, winwaitmode)){
		case WAIT_OBJECT_0:
			return 0;
		case WAIT_TIMEOUT: 
			set_yunoerror(YUNOBUSY);
			return 1;
		default:
			set_yunoerror(YUNOOS_ERROR);
			return 1;
	}
}
