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

int __stdcall start_yunothread (yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		HANDLE currentthread = get_current_thread();
		if (currentthread == NULL){
			return 1;
		}
		if (thread->thread != currentthread){
			if (ResumeThread(thread->thread) == (DWORD)-1){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
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
