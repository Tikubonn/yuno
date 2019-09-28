#include <yuno.private>
#include <stdlib.h>

yunomutex_status __stdcall free_yunomutex (yunomutex *mutex){
	free(mutex);
	return YUNOMUTEX_SUCCESS;
}
