#include <yuno.private>
#include <sys/types.h>
#include <unistd.h>

yunofile_status __yunocall tell_yunofile (yunofile *file, yunosize *seekp){
  if (file->asyncp == true){
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    *seekp = file->asyncseek;
    return YUNOFILE_SUCCESS;
  }
  else {
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    off_t seek = lseek(file->fd, 0, SEEK_CUR);
    if (seek == -1){
      return YUNOFILE_ERROR;
    }
    *seekp = seek;
    return YUNOFILE_SUCCESS;
  }
}

