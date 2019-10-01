#include <yuno.private>
#include <stdlib.h>

yunothread __yunocall *make_yunothread (yunothread_entry_point entrypoint, void *parameter){
	yunothread *thread = malloc(sizeof(yunothread));
	if (thread == NULL){
		return NULL;
	}
	if (make_yunothread_manually(entrypoint, parameter, thread) != YUNOTHREAD_SUCCESS){
		free(thread);
		return NULL;
	}
	return thread;
}
