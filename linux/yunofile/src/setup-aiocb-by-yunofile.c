#include <yuno.private>
#include <aio.h>
#include <signal.h>

void setup_aiocb_by_yunofile (void *sequence, yunosize size, yunofile *file, struct aiocb *cb){
  struct sigevent sevent;
  sevent.sigev_notify = SIGEV_NONE;
  cb->aio_fildes = file->fd;
  cb->aio_offset = file->asyncseek;
  cb->aio_buf = sequence;
  cb->aio_nbytes = size;
  cb->aio_reqprio = 0;
  cb->aio_sigevent = sevent;
}

