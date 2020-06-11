#include <yuno.h>
#include <windows.h>

int __stdcall release_yunosemaphore (yunosemaphore *semaphore){
	reset_yunoerror();
	if (ReleaseSemaphore(semaphore->semaphore, 1, NULL) == 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	return 0;
}
