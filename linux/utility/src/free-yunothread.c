#include <yuno.h>

int free_yunothread (yunothread *thread){
	return free_yunomemory(thread, sizeof(yunothread));
}
