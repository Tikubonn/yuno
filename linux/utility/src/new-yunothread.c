#include <yuno.h>

yunothread *new_yunothread (yunoentrypoint entrypoint, void *parameter){
	yunothread *thread = allocate_yunomemory(sizeof(yunothread));
	if (thread == NULL){
		return NULL;
	}
	if (make_yunothread(entrypoint, parameter, thread) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(thread, sizeof(yunothread));
		set_yunoerror(lasterror);
		return NULL;
	}
	return thread;
}
