#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

#define BOOLEAN(value) (value ? true: false)

bool __stdcall yunofile_readablep (yunofile *file){
	reset_yunoerror();
	return BOOLEAN(file->mode & YUNOFILE_READABLE);
}
