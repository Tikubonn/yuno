#include <yuno.private>
#include <stdlib.h>

yunoprocess __yunocall *make_yunoprocess (yunoprocess_entry_point entrypoint, void *parameter){
	yunoprocess *process = malloc(sizeof(yunoprocess));
	if (process == NULL){
		return NULL;
	}
	if (make_yunoprocess_manually(entrypoint, parameter, process) != YUNOPROCESS_SUCCESS){
		free(process);
		return NULL;
	}
	return process;
}
