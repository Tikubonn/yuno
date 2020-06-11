#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

bool __stdcall yunofile_closedp (yunofile *file){
	reset_yunoerror();
	return file->closedp;
}
