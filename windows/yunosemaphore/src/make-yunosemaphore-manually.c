#include <yuno.private>
#include <windows.h>

yunosemaphore_status __yunocall make_yunosemaphore_manually (int maxcount, yunosemaphore *semaphore){
	if (0 < maxcount){
		SECURITY_ATTRIBUTES secattr;
		secattr.nLength = sizeof(secattr);
		secattr.lpSecurityDescriptor = NULL;
		secattr.bInheritHandle = TRUE;
		//HANDLE handle = CreateSemaphore(&secattr, maxcount, maxcount, NULL);
		HANDLE handle = CreateSemaphore(NULL, maxcount, maxcount, NULL);
		if (handle == NULL){
			return YUNOSEMAPHORE_ERROR;
		}
		semaphore->semaphore = handle;
		return YUNOSEMAPHORE_SUCCESS;
	}
	return YUNOSEMAPHORE_ERROR;
}
