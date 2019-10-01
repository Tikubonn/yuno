#include <yuno.private>
#include <aio.h>
#include <unistd.h>

yunofile_status __yunocall request_write_yunofile (void *sequence, yunosize size, yunofile *file){
  if (file->asyncp == true){
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    map_yunofile_buffer(sequence, size, &(file->buffer));
    yunosize si = yunofile_buffer_size(&(file->buffer));
    void *seq = yunofile_buffer_array(&(file->buffer));
    setup_aiocb_by_yunofile(seq, si, file, &(file->cb));
    if (aio_write(&(file->cb)) == -1){
      return YUNOFILE_ERROR;
    }
    file->requeststatus = YUNOFILE_WRITING;
    return YUNOFILE_SUCCESS;
  }
  else {
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    ssize_t wrotesize = write(file->fd, sequence, size);
    if (wrotesize == -1){
      return YUNOFILE_ERROR;
    }
    file->requeststatus = YUNOFILE_WRITE_COMPLETED;
    file->completedsize = wrotesize;
    return YUNOFILE_SUCCESS;
  }
}

