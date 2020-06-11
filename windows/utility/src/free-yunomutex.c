#include <yuno.h>
#include <windows.h>

int __stdcall __free_yunomutex (yunomutex *mutex, yunomemory **globalmemoryp){
	return __free_yunomemory(mutex, sizeof(yunomutex), globalmemoryp);
}
