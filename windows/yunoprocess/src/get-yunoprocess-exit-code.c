#include <yuno.private>
#include <windows.h>

yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess *process, int *exitcodep){
	DWORD exitcode;
	if (GetExitCodeProcess(process->process, &exitcode) == 0){
		return YUNOPROCESS_ERROR;
	}
	*exitcodep = exitcode;
	return YUNOPROCESS_SUCCESS;
}
