#include <yuno.private>
#include <unistd.h>

yunofile_status __yunocall read_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep){
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
    ssize_t readsize = read(file->fd, sequence, size);
    if (readsize == -1){
      return YUNOFILE_ERROR;
    }
    *readsizep = readsize;
    return YUNOFILE_SUCCESS;
  }
}

