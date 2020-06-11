#include <yuno.h>
#include <stdbool.h>

inline void init_yunofile (int filefd, int mode, bool asyncp, void *bufferseq, yunosize buffersize, yunofile *file){
	file->filefd = filefd;
	file->mode = mode;
	file->asyncp = asyncp;
	file->asyncstatus = YUNOFILE_FREE;
	file->asynccompletedsize = 0; // unnecessary initialization!
	init_yunobuffer(bufferseq, buffersize, &(file->asyncbuffer));
	file->closedp = false;
}
