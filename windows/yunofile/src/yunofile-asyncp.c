#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

bool __stdcall yunofile_asyncp (yunofile *file){
	return file->asyncp == true;
}
