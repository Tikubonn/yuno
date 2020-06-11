#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

inline void init_yunofile (yunofile_type type, int mode, HANDLE filehandle, bool asyncp, HANDLE event, void *bufferseq, yunosize buffersize, yunosize asyncseek, yunofile *file){
	file->type = type;
	file->mode = mode;
	file->file = filehandle;
	file->event = event;
	file->asyncp = asyncp;
	file->asyncseek = asyncseek;
	file->asyncstatus = YUNOFILE_FREE;
	file->asynccompletedsize = 0; // initialization is unnecessary.
	//file->asyncoverlapped;
	init_yunobuffer(bufferseq, buffersize, &(file->asyncbuffer));
	file->closedp = false; 
}
