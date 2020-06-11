#include <yuno.h>
#include <windows.h>

int __stdcall close_yunoprocess (yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		if (CloseHandle(process->process) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		if (CloseHandle(process->thread) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		if (CloseHandle(process->remotethread) == 0){
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
