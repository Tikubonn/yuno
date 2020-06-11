#include <yuno.h>
#include <windows.h>

static inline DWORD __stdcall entrypoint_wrapper (LPVOID parameter){
	reset_yunoerror();
	int exitcode = 
		((yunothread*)parameter)->entrypoint(
			((yunothread*)parameter)->parameter);
	ExitThread(exitcode);
	return 0;
}

int __stdcall make_yunothread (yunoentrypoint entrypoint, void *parameter, yunothread *thread){
	reset_yunoerror();
	thread->entrypoint = entrypoint;
	thread->parameter = parameter;
	thread->closedp = false;
	HANDLE winthread = CreateThread(NULL, 0, entrypoint_wrapper, thread, CREATE_SUSPENDED, NULL);
	if (winthread == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	thread->thread = winthread;
	return 0;
}
