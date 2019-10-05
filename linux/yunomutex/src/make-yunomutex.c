#include <yuno.private>
#include <stdlib.h>

yunomutex __yunocall *make_yunomutex (){
	yunomutex *mutex = malloc(sizeof(yunomutex));
	if (mutex == NULL){
		return NULL;
	}
	if (make_yunomutex_manually(mutex) != YUNOMUTEX_SUCCESS){
		free(mutex);
		return NULL;
	}
	return mutex;
}
