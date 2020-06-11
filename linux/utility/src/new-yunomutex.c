#include <yuno.h>

yunomutex *new_yunomutex (){
	yunomutex *mutex = allocate_yunomemory(sizeof(yunomutex));
	if (mutex == NULL){
		return NULL;
	}
	if (make_yunomutex(mutex) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(mutex, sizeof(yunomutex));
		set_yunoerror(lasterror);
		return NULL;
	}
	return mutex;
}
