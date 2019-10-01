#include <yuno.private>
#include <stdlib.h>

yunomutex __yunocall *make_named_yunomutex (const char *name){
	yunomutex *mutex = malloc(sizeof(yunomutex));
	if (mutex == NULL){
		return NULL;
	}
	if (make_named_yunomutex_manually(name, mutex) != YUNOMUTEX_SUCCESS){
		free(mutex);
		return NULL;
	}
	return mutex;
}
