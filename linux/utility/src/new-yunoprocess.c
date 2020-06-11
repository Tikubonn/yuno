#include <yuno.h>

yunoprocess *new_yunoprocess (yunoentrypoint entrypoint, void *parameter){
	yunoprocess *process = allocate_yunomemory(sizeof(yunoprocess));
	if (process == NULL){
		return NULL;
	}
	if (make_yunoprocess(entrypoint, parameter, process) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(process, sizeof(yunoprocess));
		set_yunoerror(lasterror);
		return NULL;
	}
	return process;
}
