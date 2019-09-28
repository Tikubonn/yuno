#include <yuno.private>
#include <windows.h>

yunomutex_status __stdcall close_yunomutex (yunomutex *mutex){
	if (CloseHandle(mutex->mutex) == 0){
		return YUNOMUTEX_ERROR;
	}
	return YUNOMUTEX_SUCCESS;
}
