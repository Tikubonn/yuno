#include <yuno.h>
#include <windows.h>

int __stdcall __free_yunothread (yunothread *thread, yunomemory **globalmemoryp){
	return __free_yunomemory(thread, sizeof(yunothread), globalmemoryp);
}
