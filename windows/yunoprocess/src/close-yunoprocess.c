#include <yuno.private>
#include <windows.h>

yunoprocess_status __yunocall close_yunoprocess (yunoprocess *process){
	if (CloseHandle(process->process) == 0){
		return YUNOPROCESS_ERROR;
	}
	if (CloseHandle(process->thread) == 0){
		return YUNOPROCESS_ERROR;
	}
	if (CloseHandle(process->remotethread) == 0){
		return YUNOPROCESS_ERROR;
	}
	return YUNOPROCESS_SUCCESS;
}
