#include <yuno.h>
#include <windows.h>

static void setup_security_attributes (SECURITY_ATTRIBUTES *secattrs){
	secattrs->nLength = sizeof(SECURITY_ATTRIBUTES);
	secattrs->lpSecurityDescriptor = NULL;
	secattrs->bInheritHandle = TRUE;
}

int __stdcall make_yunosemaphore (yunosize maxcount, yunosemaphore *semaphore){
	reset_yunoerror();
	SECURITY_ATTRIBUTES secattrs;
	setup_security_attributes(&secattrs);
	HANDLE winsemaphore = CreateSemaphore(&secattrs, maxcount, maxcount, NULL);
	if (winsemaphore == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	semaphore->semaphore = winsemaphore;
	return 0;
}
