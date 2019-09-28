#include <yuno.private>
#include <stdlib.h>

yunosemaphore_status __stdcall free_yunosemaphore (yunosemaphore *semaphore){
	free(semaphore);
	return YUNOMUTEX_SUCCESS;
}
