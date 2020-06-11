#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static inline int parse_flags (int flags, bool *asyncp, DWORD *accessp, DWORD *sharep, DWORD *creationp){
	reset_yunoerror();
	int asyncflags = flags & (YUNOFILE_SYNC | YUNOFILE_ASYNC);
	switch (asyncflags){
		case 0:
			*asyncp = false;
			break;
		case YUNOFILE_SYNC:
			*asyncp = false;
			break;
		case YUNOFILE_ASYNC:
			*asyncp = true;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	int fileflags = flags & ~(YUNOFILE_ASYNC | YUNOFILE_SYNC);
  switch (fileflags){
		case YUNOFILE_READABLE: 
			*accessp = GENERIC_READ;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_EXISTING;
			return 0;
		case YUNOFILE_WRITABLE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_WRITABLE | YUNOFILE_APPEND: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_APPEND: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
    default:
    	set_yunoerror(YUNOARGUMENT_ERROR);
      return 1;
  }
}

static inline int open_async_file (const char *filename, int flags, DWORD access, DWORD share, DWORD creation, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	HANDLE handle = CreateFile(filename, access, share, NULL, creation, FILE_FLAG_OVERLAPPED, NULL);
	if (handle == INVALID_HANDLE_VALUE){
		switch (GetLastError()){
			case ERROR_FILE_NOT_FOUND:
				set_yunoerror(YUNODOES_NOT_EXIST);
				return 1;
			case ERROR_PATH_NOT_FOUND:
				set_yunoerror(YUNODOES_NOT_EXIST);
				return 1;
			default:
				set_yunoerror(YUNOOS_ERROR);
				return 1;
		}
	}
	HANDLE event = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event == INVALID_HANDLE_VALUE){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	yunosize asyncseek = 0;
	if (flags & YUNOFILE_APPEND){
		LARGE_INTEGER filesize;
		if (GetFileSizeEx(handle, &filesize) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		asyncseek = filesize.QuadPart;
	}
	init_yunofile(TYPE_YUNOFILE, flags, handle, true, event, bufferseq, buffersize, asyncseek, file);
	return 0;
}

static inline int open_sync_file (const char *filename, int flags, DWORD access, DWORD share, DWORD creation, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	HANDLE handle = CreateFile(filename, access, share, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle == INVALID_HANDLE_VALUE){
		switch (GetLastError()){
			case ERROR_FILE_NOT_FOUND:
				set_yunoerror(YUNODOES_NOT_EXIST);
				return 1;
			case ERROR_PATH_NOT_FOUND:
				set_yunoerror(YUNODOES_NOT_EXIST);
				return 1;
			default:
				set_yunoerror(YUNOOS_ERROR);
				return 1;
		}
	}
	if (flags & YUNOFILE_APPEND){
		LARGE_INTEGER zero;
		zero.QuadPart = 0;
		if (SetFilePointerEx(handle, zero, NULL, FILE_END) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
	}
	init_yunofile(TYPE_YUNOFILE, flags, handle, false, NULL, bufferseq, buffersize, 0, file);
	return 0;
}

int __stdcall open_yunofile (const char *filename, int flags, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	bool asyncp;
	DWORD access;
	DWORD share;
	DWORD creation;
	if (parse_flags(flags, &asyncp, &access, &share, &creation) != 0){
		return 1;
	}
	if (asyncp == true){
		return open_async_file(filename, flags, access, share, creation, bufferseq, buffersize, file);
	}
	else {
		return open_sync_file(filename, flags, access, share, creation, bufferseq, buffersize, file);
	}
}
