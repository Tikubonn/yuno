#include <yuno.h>
#include <windows.h>

yunomutex *__stdcall __new_yunomutex (yunomemory **globalmemoryp){
	yunomutex *mutex = __allocate_yunomemory(sizeof(yunomutex), globalmemoryp);
	if (mutex == NULL){
		return NULL;
	}
	if (make_yunomutex(mutex) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(mutex, sizeof(yunomutex), globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return mutex;
}
