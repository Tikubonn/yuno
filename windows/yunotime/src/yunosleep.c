#include <yuno.private>
#include <windows.h>

yunosleep_status __stdcall yunosleep (int seconds){
	if (seconds < 0){
		return YUNOSLEEP_ERROR;
	}
	Sleep(seconds * 1000);
	return YUNOSLEEP_SUCCESS;
}
