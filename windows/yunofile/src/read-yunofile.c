#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

int __stdcall read_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncstatus == YUNOFILE_FREE){
			if (file->asyncp == true){
				if (request_read_yunofile(size, file) != 0){
					return 1;
				}
				if (wait_read_yunofile(sequence, YUNOFOREVER, file, readsizep) != 0){
					return 1;
				}
				return 0;
			}
			else {
				DWORD readsize;
				if (ReadFile(file->file, sequence, size, &readsize, NULL) == 0){
					switch (GetLastError()){
						case ERROR_BROKEN_PIPE:
							*readsizep = 0;
							return 0;
						default:
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				*readsizep = readsize;
				return 0;
			}
		}
		else {
			set_yunoerror(YUNOBUSY);
			return 1;
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
