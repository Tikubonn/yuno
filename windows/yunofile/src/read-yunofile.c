#include <yuno.private>
#include <windows.h>

yunofile_status __stdcall read_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
	if (file->asyncp == true){
		yunofile_status status1 = request_read_yunofile(size, file);
		if (status1 != YUNOFILE_SUCCESS){
			return status1;
		}
		yunofile_status status2 = wait_read_yunofile(sequence, YUNOFILE_FOREVER, file, readsizep);
		if (status2 != YUNOFILE_SUCCESS){
			return status2;
		}
		return YUNOFILE_SUCCESS;
	}
	else {
		if (file->requeststatus != YUNOFILE_FREE){
			return YUNOFILE_BUSY;
		}
		return read_sync_yunofile(sequence, size, file, readsizep);
	}
}
