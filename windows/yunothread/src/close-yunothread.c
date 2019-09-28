#include <yuno.private>
#include <windows.h>

yunothread_status __stdcall close_yunothread (yunothread *thread){
	if (CloseHandle(thread->thread) == 0){
		return YUNOTHREAD_ERROR;
	}
	return YUNOTHREAD_SUCCESS;
}
