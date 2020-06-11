#include <yuno.h>
#include <windows.h>

int __stdcall start_yunoprocess (yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		if (ResumeThread(process->remotethread) == (DWORD)-1){
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
