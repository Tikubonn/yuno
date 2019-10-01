#include <yuno.private>
#include <unistd.h>

yunofile_status __yunocall close_yunofile (yunofile *file){
  if (close(file->fd) == -1){
    return YUNOFILE_ERROR;
  }
  return YUNOFILE_SUCCESS;
}

