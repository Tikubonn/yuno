#include <yuno.private>
#include <stdlib.h>

yunothread_status __yunocall free_yunothread (yunothread *thread){
	free(thread);
	return YUNOTHREAD_SUCCESS;
}
