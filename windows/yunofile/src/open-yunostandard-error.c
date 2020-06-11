#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

static int parse_flags (int flags, bool *asyncp){
	reset_yunoerror();
	switch (flags){
		case 0:
			*asyncp = false;
			return 0;
		case YUNOFILE_SYNC:
			*asyncp = false;
			return 0;
		case YUNOFILE_ASYNC:
			*asyncp = true;
			return 0;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
}

int __stdcall open_yunostandard_error (int flags, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	bool asyncp;
	if (parse_flags(flags, &asyncp) != 0){
		return 1;
	}
	HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
	if (handle == INVALID_HANDLE_VALUE){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	if (handle == NULL){
		set_yunoerror(YUNODOES_NOT_EXIST);
		return 1;
	}
	init_yunofile(TYPE_YUNOFILE, YUNOFILE_WRITABLE, handle, asyncp, NULL, bufferseq, buffersize, 0, file);
	return 0;
}
