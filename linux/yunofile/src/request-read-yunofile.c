#include <yuno.private>
#include <aio.h>
#include <unistd.h>
#define min(a, b) ((a)<(b)?(a):(b))

yunofile_status __yunocall request_read_yunofile (yunosize size, yunofile *file){
  if (file->asyncp == true){
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    yunosize si = min(size, yunofile_buffer_max_size(&(file->buffer)));
    void *seq = yunofile_buffer_array(&(file->buffer));
    setup_aiocb_by_yunofile(seq, si, file, &(file->cb));
    if (aio_read(&(file->cb)) == -1){
      return YUNOFILE_ERROR;
    }
    file->requeststatus = YUNOFILE_READING;
    return YUNOFILE_SUCCESS;
  }
  else {
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    yunosize si = min(size, yunofile_buffer_max_size(&(file->buffer)));
    void *seq = yunofile_buffer_array(&(file->buffer));
    ssize_t readsize = read(file->fd, seq, si);
    if (readsize == -1){
      return YUNOFILE_ERROR;
    }
    file->requeststatus = YUNOFILE_READ_COMPLETED;
    file->completedsize = readsize;
    return YUNOFILE_SUCCESS;
  }
}

