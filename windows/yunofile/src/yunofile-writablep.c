#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

#define BOOLEAN(value) (value ? true: false)

bool __stdcall yunofile_writablep (yunofile *file){
	reset_yunoerror();
	return BOOLEAN(file->mode & YUNOFILE_WRITABLE);
}
