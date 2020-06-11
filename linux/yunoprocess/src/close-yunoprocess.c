#include <yuno.h>

int close_yunoprocess (yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		if (process->exitedp == true){
			process->closedp = true;
			return 0;
		}
		else {
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
