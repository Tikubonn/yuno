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

int __stdcall open_yunostandard_output (int flags, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	bool asyncp;
	if (parse_flags(flags, &asyncp) != 0){
		return 1;
	}
	if (asyncp == true){
		HANDLE handle = CreateFile("CONOUT$", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		if (handle == INVALID_HANDLE_VALUE){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		HANDLE event = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (event == INVALID_HANDLE_VALUE){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		init_yunofile(TYPE_YUNOFILE, YUNOFILE_WRITABLE, handle, true, event, bufferseq, buffersize, 0, file);
		return 0;
	}
	else {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handle == INVALID_HANDLE_VALUE){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		if (handle == NULL){
			set_yunoerror(YUNODOES_NOT_EXIST);
			return 1;
		}
		init_yunofile(TYPE_YUNOFILE, YUNOFILE_WRITABLE, handle, false, NULL, bufferseq, buffersize, 0, file);
		return 0;
	}
}
