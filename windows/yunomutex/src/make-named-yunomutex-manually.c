#include <yuno.private>
#include <windows.h>

yunomutex_status __stdcall make_named_yunomutex_manually (const char *name, yunomutex *mutex){
	if (name == NULL){
		return YUNOSEMAPHORE_ERROR;
	}
	SECURITY_ATTRIBUTES secattr;
	secattr.nLength = sizeof(secattr);
	secattr.lpSecurityDescriptor = NULL;
	secattr.bInheritHandle = TRUE;
	HANDLE handle = CreateMutex(&secattr, FALSE, name);
	if (handle == NULL){
		return YUNOMUTEX_ERROR;
	}
	mutex->mutex = handle;
	return YUNOMUTEX_SUCCESS;
}
