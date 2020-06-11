#include <yuno.h>
#include <windows.h>

yunoerror __stdcall get_yunoerror (){
	return thread_yunoerror;
}
