#include <yuno.private>
#include <windows.h>

yunosemaphore_status __stdcall make_named_yunosemaphore_manually (const char *name, int maxcount, yunosemaphore *semaphore){
	if (name == NULL){
		return YUNOSEMAPHORE_ERROR;
	}
	SECURITY_ATTRIBUTES secattr;
	secattr.nLength = sizeof(secattr);
	secattr.lpSecurityDescriptor = NULL;
	secattr.bInheritHandle = TRUE;
	HANDLE handle = CreateSemaphore(&secattr, maxcount, maxcount, name);
	if (handle == NULL){
		return YUNOSEMAPHORE_ERROR;
	}
	semaphore->semaphore = handle;
	return YUNOSEMAPHORE_SUCCESS;
}
