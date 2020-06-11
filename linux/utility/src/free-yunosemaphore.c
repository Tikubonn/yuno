#include <yuno.h>

int free_yunosemaphore (yunosemaphore *semaphore){
	return free_yunomemory(semaphore, sizeof(yunosemaphore));
}
