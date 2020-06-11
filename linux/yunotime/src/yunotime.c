#include <yuno.h>
#include <time.h>

int yunotime (yunoseconds *secondsp){
	reset_yunoerror();
	*secondsp = time(NULL);
	return 0;
}
