#include <yuno.private>
#include <windows.h>
#include <stdbool.h>

void init_yunofile (int mode, HANDLE handle, void *bufferseq, yunosize buffersize, yunofile *file){
	file->mode = mode;
	file->file = handle;
	file->asyncp = false;
	file->asyncseek = 0; //! 不定値でも可
	file->requeststatus = YUNOFILE_FREE; //! 不定値でも可
	file->completedsize = 0; //! 不定値でも可
	init_yunofile_buffer(bufferseq, buffersize, &(file->buffer));
}
