#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall request_write_yunofile (void *sequence, yunosize size, yunofile *file){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY; // now busy!
		}
		yunosize si = map_yunofile_buffer(sequence, size, &(file->buffer));
		void *seq = yunofile_buffer_array(&(file->buffer));
		setup_yunofile_overlapped(file->asyncseek, &(file->overlapped));
		DWORD wrotesize;
		if (WriteFile(file->file, seq, si, &wrotesize, &(file->overlapped)) == 0){
			switch (GetLastError()){
				case ERROR_IO_PENDING: {
					file->requeststatus = YUNOFILE_WRITING;
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
		yunosize wrotesize;
		if (write_sync_yunofile(sequence, size, file, &wrotesize) != YUNOFILE_SUCCESS){
			return YUNOFILE_ERROR;
		}
		file->requeststatus = YUNOFILE_WRITE_COMPLETED;
		file->completedsize = wrotesize;
		return YUNOFILE_SUCCESS;
	}
}
