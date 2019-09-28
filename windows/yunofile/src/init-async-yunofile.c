#include <yuno.private>
#include <windows.h>
#include <stdbool.h>

void init_async_yunofile (int mode, HANDLE handle, void *bufferseq, yunosize buffersize, yunosize seek, yunofile *file){
	file->mode = mode;
	file->file = handle;
	file->asyncp = true;
	file->asyncseek = seek;
	file->requeststatus = YUNOFILE_FREE;
	file->completedsize = 0;
	init_yunofile_buffer(bufferseq, buffersize, &(file->buffer));
}
