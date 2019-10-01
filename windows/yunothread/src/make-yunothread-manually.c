#include <yuno.private>
#include <windows.h>

static DWORD __yunocall __yunothread_entry_point (LPVOID parameter){
	int exitcode = 
		((yunothread*)parameter)->entrypoint(
			((yunothread*)parameter)->parameter);
	ExitThread(exitcode);
	return 0;
}

yunothread_status __yunocall make_yunothread_manually (yunothread_entry_point entrypoint, void *parameter, yunothread *threadp){
	threadp->entrypoint = entrypoint;
	threadp->parameter = parameter;
	HANDLE thread = CreateThread(NULL, 0, __yunothread_entry_point, threadp, CREATE_SUSPENDED, NULL);
	if (thread == NULL){
		return YUNOTHREAD_ERROR;
	}
	threadp->thread = thread;
	return YUNOTHREAD_SUCCESS;
}
