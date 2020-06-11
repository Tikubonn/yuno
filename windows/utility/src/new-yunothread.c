#include <yuno.h>
#include <windows.h>

yunothread *__stdcall __new_yunothread (yunoentrypoint entrypoint, void *parameter, yunomemory **globalmemoryp){
	yunothread *thread = __allocate_yunomemory(sizeof(yunothread), globalmemoryp);
	if (thread == NULL){
		return NULL;
	}
	if (make_yunothread(entrypoint, parameter, thread) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(thread, sizeof(yunothread), globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return thread;
}
