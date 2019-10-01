#include <yuno.private>
#include <stdlib.h>

yunoprocess_status __yunocall free_yunoprocess (yunoprocess *process){
	free(process);
	return YUNOPROCESS_SUCCESS;
}
