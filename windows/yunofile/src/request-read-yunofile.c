#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

int __stdcall request_read_yunofile (yunosize size, yunofile *file){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncstatus == YUNOFILE_FREE){
			if (file->asyncp == true){
				clear_yunobuffer(&(file->asyncbuffer));
				void *bufferarray = yunobuffer_array(&(file->asyncbuffer));
				yunosize buffersize = yunobuffer_size(&(file->asyncbuffer));
				setup_yunofile_overlapped(file->asyncseek, file->event, &(file->asyncoverlapped));
				DWORD dummy;
				if (ReadFile(file->file, bufferarray, MIN(buffersize, size), &dummy, &(file->asyncoverlapped)) == 0){
					switch (GetLastError()){
						case ERROR_BROKEN_PIPE:
							file->asyncstatus = YUNOFILE_READ_COMPLETED;
							file->asynccompletedsize = 0;
							return 0;
						case ERROR_IO_PENDING: 
							file->asyncstatus = YUNOFILE_READING;
							return 0;
						default:
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				switch (file->type){
					case TYPE_YUNOSERVER_PIPE:
						file->asyncstatus = YUNOFILE_READING;
						return 0;
					case TYPE_YUNOCLIENT_PIPE:
						file->asyncstatus = YUNOFILE_READING;
						return 0;
					default:
						set_yunoerror(YUNOOS_ERROR);
						return 1;
				}
			}
			else {
				clear_yunobuffer(&(file->asyncbuffer));
				void *bufferarray = yunobuffer_array(&(file->asyncbuffer));
				yunosize buffersize = yunobuffer_size(&(file->asyncbuffer));
				DWORD readsize;
				if (ReadFile(file->file, bufferarray, MIN(buffersize, size), &readsize, NULL) == 0){
					set_yunoerror(YUNOOS_ERROR);
					return 1;
				}
				if (set_yunobuffer_end(readsize, &(file->asyncbuffer)) != 0){
					set_yunoerror(YUNOERROR);
					return 1;
				}
				file->asyncstatus = YUNOFILE_READ_COMPLETED;
				file->asynccompletedsize = readsize;
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
