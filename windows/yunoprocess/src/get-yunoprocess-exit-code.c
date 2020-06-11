#include <yuno.h>
#include <windows.h>

int __stdcall get_yunoprocess_exit_code (yunoprocess *process, int *exitcodep){
	reset_yunoerror();
	if (process->closedp == false){
		DWORD exitcode;
		if (GetExitCodeProcess(process->process, &exitcode) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		*exitcodep = exitcode;
		return 0;
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
