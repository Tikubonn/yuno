#include <yuno.private>
#include <windows.h>

yunomutex_status __yunocall make_yunomutex_manually (yunomutex *mutex){
	SECURITY_ATTRIBUTES secattr;
	secattr.nLength = sizeof(secattr);
	secattr.lpSecurityDescriptor = NULL;
	secattr.bInheritHandle = TRUE;
	HANDLE handle = CreateMutex(&secattr, FALSE, NULL);
	if (handle == NULL){
		return YUNOMUTEX_ERROR;
	}
	mutex->mutex = handle;
	return YUNOMUTEX_SUCCESS;
}
