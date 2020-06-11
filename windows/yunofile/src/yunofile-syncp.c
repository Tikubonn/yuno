#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

bool __stdcall yunofile_syncp (yunofile *file){
	return file->asyncp == false;
}
