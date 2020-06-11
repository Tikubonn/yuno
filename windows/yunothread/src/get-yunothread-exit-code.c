#include <yuno.h>
#include <windows.h>

static HANDLE get_current_thread (){
	reset_yunoerror();
	DWORD currentthreadid = GetCurrentThreadId();
	HANDLE currentthread = OpenThread(THREAD_ALL_ACCESS, FALSE, currentthreadid);
	if (currentthread == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	return currentthread;
}

int __stdcall get_yunothread_exit_code (yunothread *thread, int *exitcodep){
	reset_yunoerror();
	if (thread->closedp == false){
		HANDLE currentthread = get_current_thread();
		if (currentthread == NULL){
			return 1;
		}
		if (thread->thread != currentthread){
			DWORD exitcode;
			if (GetExitCodeThread(thread->thread, &exitcode) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			*exitcodep = exitcode;
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
