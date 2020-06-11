#include <yuno.h>
#include <windows.h>

int __stdcall close_yunothread (yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		if (CloseHandle(thread->thread) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		return 0;
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
