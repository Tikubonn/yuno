#include <yuno.private>
#include <unistd.h>

yunofile_status __yunocall write_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep){
  if (file->asyncp == true){
    yunofile_status status1 = request_write_yunofile(sequence, size, file);
    if (status1 != YUNOFILE_SUCCESS){
      return status1;
    }
    yunofile_status status2 = wait_write_yunofile(YUNOFILE_FOREVER, file, wrotesizep);
    if (status2 != YUNOFILE_SUCCESS){
      return status2;
    }
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
    *wrotesizep = wrotesize;
    return YUNOFILE_SUCCESS;
  }
}

