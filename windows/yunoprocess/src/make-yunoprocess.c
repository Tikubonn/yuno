#include <yuno.private>
#include <stdlib.h>

yunoprocess __yunocall *__make_yunoprocess (yunoprocess_entry_point entrypoint, void *parameter, yunoshared_memory **sharedmemoryp){
	yunoprocess *process = malloc(sizeof(yunoprocess));
	if (process == NULL){
		return NULL;
	}
	if (__make_yunoprocess_manually(entrypoint, parameter, process, sharedmemoryp) != YUNOPROCESS_SUCCESS){
		free(process);
		return NULL;
	}
	return process;
}
