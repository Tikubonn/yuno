#include <yuno.private>
#include <windows.h>

yunothread_status __stdcall start_yunothread (yunothread *thread){
	if (ResumeThread(thread->thread) == -1){
		return YUNOTHREAD_ERROR;
	}
	return YUNOTHREAD_SUCCESS;
}
