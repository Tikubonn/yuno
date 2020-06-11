#include <yuno.h>
#include <windows.h>

int __stdcall close_yunosemaphore (yunosemaphore *semaphore){
	reset_yunoerror();
	if (CloseHandle(semaphore->semaphore) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	return 0;
}
