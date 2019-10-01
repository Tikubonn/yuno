#include <yuno.private>
#include <windows.h>

static void copy_from_buffer (void *sequence, yunosize size, yunofile_buffer *buffer){
	void *bufferseq = yunofile_buffer_array(buffer);
	for (yunosize index = 0; index < size; index++){
		((char*)sequence)[index] = 
			((char*)bufferseq)[index];
	}
}

yunofile_status __yunocall wait_read_yunofile (void *sequence, yunofile_wait_mode waitmode, yunofile *file, yunosize *readsizep){
	if (file->asyncp == true){
		if (file->requeststatus != YUNOFILE_READING){
			return YUNOFILE_ERROR;
		}
		BOOL wait;
		switch (waitmode){
			case YUNOFILE_FOREVER: 
				wait = TRUE;
				break;
			case YUNOFILE_NOWAIT: 
				wait = FALSE;
				break;
			default: 
				return YUNOFILE_ERROR;
		}
		DWORD readsize;
		if (GetOverlappedResult(file->file, &(file->overlapped), &readsize, wait) == 0){
			switch (GetLastError()){
				case ERROR_IO_PENDING: {
					return YUNOFILE_BUSY; // now busy!
				}
				case ERROR_BROKEN_PIPE: {
					file->requeststatus = YUNOFILE_FREE;
					*readsizep = 0;
					return YUNOFILE_SUCCESS;
				}
				case ERROR_HANDLE_EOF: {
					file->requeststatus = YUNOFILE_FREE;
					*readsizep = 0;
					return YUNOFILE_SUCCESS;
				}
				default: {
					return YUNOFILE_ERROR;
				}
			}
		}
		else {
			copy_from_buffer(sequence, readsize, &(file->buffer));
			file->requeststatus = YUNOFILE_FREE;
			file->asyncseek += readsize;
			*readsizep = readsize;
			return YUNOFILE_SUCCESS;
		}
	}
	else {
		if (file->requeststatus != YUNOFILE_READ_COMPLETED){
			return YUNOFILE_ERROR;
		}
		copy_from_buffer(sequence, file->completedsize, &(file->buffer));
		file->requeststatus = YUNOFILE_FREE;
		*readsizep = file->completedsize;
		return YUNOFILE_SUCCESS;
	}
}
