#include <yuno.private>
#include <stdlib.h>

yunoprocess_status __stdcall free_yunoprocess (yunoprocess *process){
	free(process);
	return YUNOPROCESS_SUCCESS;
}
