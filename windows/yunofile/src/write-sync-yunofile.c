#include <yuno.private>
#include <windows.h>

yunofile_status write_sync_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
	DWORD wrotesize;
	if (WriteFile(file->file, sequence, size, &wrotesize, NULL) == 0){
		return YUNOFILE_ERROR;
	}
	*wrotesizep = wrotesize;
	return YUNOFILE_SUCCESS;
}
