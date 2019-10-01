#include <yuno.private>
#include <stdbool.h>

void init_yunofile (int fd, int mode, void *bufferseq, yunosize buffersize, yunofile *file){
  file->fd = fd;
  file->mode = mode;
  file->asyncp = false;
  file->asyncseek = 0;
  file->requeststatus = YUNOFILE_FREE;
  init_yunofile_buffer(bufferseq, buffersize, &(file->buffer));
}

