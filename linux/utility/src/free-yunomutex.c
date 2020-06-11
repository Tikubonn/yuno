#include <yuno.h>

int free_yunomutex (yunomutex *mutex){
	return free_yunomemory(mutex, sizeof(yunomutex));
}
