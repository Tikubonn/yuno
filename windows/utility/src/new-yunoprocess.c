#include <yuno.h>
#include <windows.h>

yunoprocess *__stdcall __new_yunoprocess (yunoentrypoint entrypoint, void *parameter, yunomemory **globalmemoryp, yunoshared_memory **globalsharedmemoryp){
	yunoprocess *process = __allocate_yunomemory(sizeof(yunoprocess), globalmemoryp);
	if (process == NULL){
		return NULL;
	}
	if (__make_yunoprocess(entrypoint, parameter, globalmemoryp, globalsharedmemoryp, process) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(process, sizeof(yunoprocess), globalmemoryp);
		set_yunoerror(lasterror);
		return NULL;
	}
	return process;
}
