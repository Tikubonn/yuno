#include <yuno.h>

int free_yunoprocess (yunoprocess *process){
	return free_yunomemory(process, sizeof(yunoprocess));
}
