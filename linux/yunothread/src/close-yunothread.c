#include <yuno.h>

int close_yunothread (yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		if (thread->exitedp == true){
			thread->closedp = true;
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
