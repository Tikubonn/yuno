#include <yuno.private>
#include <windows.h>
#define min(a, b) ((a)<(b)?(a):(b))

yunofile_status __yunocall request_read_yunofile (yunosize size, yunofile *file){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		yunosize si = min(size, yunofile_buffer_max_size(&(file->buffer)));
		void *seq = yunofile_buffer_array(&(file->buffer));
		setup_yunofile_overlapped(file->asyncseek, &(file->overlapped));
		DWORD readsize;
		if (ReadFile(file->file, seq, si, &readsize, &(file->overlapped)) == 0){
			switch (GetLastError()){
				case ERROR_IO_PENDING: {
					file->requeststatus = YUNOFILE_READING;
					return YUNOFILE_SUCCESS;
				}
				default: {
					return YUNOFILE_ERROR;
				}
			}
		}
		else {
			return YUNOFILE_ERROR; // unknown status!
		}
	}
	else {
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		yunosize si = min(size, yunofile_buffer_max_size(&(file->buffer)));
		void *array = yunofile_buffer_array(&(file->buffer));
		yunosize readsize;
		if (read_sync_yunofile(array, si, file, &readsize) != YUNOFILE_SUCCESS){
			return YUNOFILE_ERROR;
		}
		file->requeststatus = YUNOFILE_READ_COMPLETED;
		file->completedsize = readsize;
		return YUNOFILE_SUCCESS;
	}
}
