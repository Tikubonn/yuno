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

static int try_wait (yunowait_mode waitmode, yunothread *thread){
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
	switch (WaitForSingleObject(thread->thread, winwaitmode)){
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

int __stdcall wait_yunothread (yunowait_mode waitmode, yunothread *thread){
	reset_yunoerror();
	if (thread->closedp == false){
		HANDLE currentthread = get_current_thread();
		if (currentthread == NULL){
			return 1;
		}
		if (thread->thread != currentthread){
			return try_wait(waitmode, thread);
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
