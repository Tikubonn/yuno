#include <yuno.private>
#include <windows.h>

yunomutex_status __yunocall release_yunomutex (yunomutex *mutex){
	if (ReleaseMutex(mutex->mutex) == 0){
		return YUNOMUTEX_ERROR;
	}
	return YUNOMUTEX_SUCCESS;
}
