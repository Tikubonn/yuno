#include <yuno.private>
#include <windows.h>

yunoprocess_status __yunocall start_yunoprocess (yunoprocess *process){
	if (ResumeThread(process->remotethread) == -1){
		return YUNOPROCESS_ERROR;
	}
	return YUNOPROCESS_SUCCESS;
}
