#include <yuno.private>
#include <stdlib.h>

yunothread_status __stdcall free_yunothread (yunothread *thread){
	free(thread);
	return YUNOTHREAD_SUCCESS;
}
