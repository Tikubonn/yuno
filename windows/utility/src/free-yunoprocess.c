#include <yuno.h>
#include <windows.h>

int __stdcall __free_yunoprocess (yunoprocess *process, yunomemory **globalmemoryp){
	return __free_yunomemory(process, sizeof(yunoprocess), globalmemoryp);
}
