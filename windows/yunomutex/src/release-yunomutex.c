#include <yuno.h>
#include <windows.h>

int __stdcall release_yunomutex (yunomutex *mutex){
	reset_yunoerror();
	if (ReleaseMutex(mutex->mutex) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	return 0;
}
