#include <yuno.h>
#include <windows.h>

static HANDLE get_current_process (){
	reset_yunoerror();
	DWORD currentprocessid = GetCurrentProcessId();
	HANDLE currentprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, currentprocessid);
	if (currentprocess == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	return currentprocess;
}

static int try_wait (yunowait_mode waitmode, yunoprocess *process){
	DWORD winwaitmode;
	switch (waitmode){
		case YUNOFOREVER:
			winwaitmode = INFINITE;
			break;
		case YUNONOWAIT:
			winwaitmode = 0;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	switch (WaitForSingleObject(process->process, winwaitmode)){
		case WAIT_OBJECT_0:
			return 0;
		case WAIT_TIMEOUT:
			set_yunoerror(YUNOBUSY);
			return 1;
		default:
			set_yunoerror(YUNOOS_ERROR);
			return 1;
	}
}

int __stdcall wait_yunoprocess (yunowait_mode waitmode, yunoprocess *process){
	reset_yunoerror();
	if (process->closedp == false){
		HANDLE currentprocess = get_current_process();
		if (currentprocess == NULL){
			return 1;
		}
		if (process->process != currentprocess){
			return try_wait(waitmode, process);
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
