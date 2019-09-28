#include <yuno.private>
#include <windows.h>

yunothread_status __stdcall get_yunothread_exit_code (yunothread *thread, int *exitcodep){
	DWORD exitcode;
	if (GetExitCodeThread(thread->thread, &exitcode) == 0){
		return YUNOTHREAD_ERROR;
	}
	*exitcodep = exitcode;
	return YUNOTHREAD_SUCCESS;
}
