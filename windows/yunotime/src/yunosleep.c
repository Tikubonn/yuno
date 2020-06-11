#include <yuno.h>
#include <windows.h>

int __stdcall yunosleep (yunoseconds seconds, yunoseconds miliseconds){
	reset_yunoerror();
	Sleep(seconds * 1000 + miliseconds);
	return 0;
}
