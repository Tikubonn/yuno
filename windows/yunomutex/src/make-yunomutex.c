#include <yuno.h>
#include <windows.h>

static inline void setup_security_attributes (SECURITY_ATTRIBUTES *secattrs){
	secattrs->nLength = sizeof(SECURITY_ATTRIBUTES);
	secattrs->lpSecurityDescriptor = NULL;
	secattrs->bInheritHandle = TRUE;
}

int __stdcall make_yunomutex (yunomutex *mutex){
	reset_yunoerror();
	SECURITY_ATTRIBUTES secattrs;
	setup_security_attributes(&secattrs);
	HANDLE winmumtex = CreateMutex(&secattrs, FALSE, NULL);
	if (winmumtex == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	mutex->mutex = winmumtex;
	return 0;
}
