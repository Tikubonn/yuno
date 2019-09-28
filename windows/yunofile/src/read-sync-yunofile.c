#include <yuno.private>
#include <windows.h>

yunofile_status read_sync_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	DWORD readsize;
	if (ReadFile(file->file, sequence, size, &readsize, NULL) == 0){
		switch (GetLastError()){
			case ERROR_BROKEN_PIPE: 
				*readsizep = 0;
				return YUNOFILE_SUCCESS;
			default: 
				return YUNOFILE_ERROR;
		}
	}
	*readsizep = readsize;
	return YUNOFILE_SUCCESS;
}
