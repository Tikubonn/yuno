#include <yuno.private>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int __get_file_size (int fd, off_t *sizep){
  struct stat st;
  if (fstat(fd, &st) == -1){
    return 1;
  }
  *sizep = st.st_size;
  return 0;
}

yunofile_status __yunocall seek_yunofile (yunossize seek, yunofile_where where, yunofile *file, yunosize *newseekp){
  if (file->asyncp == true){
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    switch (where){
      case YUNOFILE_BEGIN: {
        if (seek < 0){
          return YUNOFILE_ERROR;
        }
        file->asyncseek = seek;
        *newseekp = seek;
        return YUNOFILE_SUCCESS;
      }
      case YUNOFILE_CURRENT: {
        yunossize newseek = file->asyncseek + seek;
        if (newseek < 0){
          return YUNOFILE_ERROR;
        }
        file->asyncseek = newseek;
        *newseekp = newseek;
        return YUNOFILE_SUCCESS;
      }
      case YUNOFILE_END: {
        off_t filesize;
        if (__get_file_size(file->fd, &filesize) != 0){
          return YUNOFILE_ERROR;
        }
        yunossize newseek = filesize + seek;
        if (newseek < 0){
          return YUNOFILE_ERROR;
        }
        file->asyncseek = newseek;
        *newseekp = newseek;
        return YUNOFILE_SUCCESS;
      }
      default: {
        return YUNOFILE_ERROR;
      }
    }
  }
  else {
    if (file->requeststatus != YUNOFILE_FREE){
      return YUNOFILE_BUSY;
    }
    int whence;
    switch (where){
      case YUNOFILE_BEGIN:
        whence = SEEK_SET;
        break;
      case YUNOFILE_CURRENT:
        whence = SEEK_CUR;
        break;
      case YUNOFILE_END:
        whence = SEEK_END;
        break;
      default:
        return YUNOFILE_ERROR;
    }
    off_t newseek = lseek(file->fd, seek, whence);
    if (newseek == -1){
      return YUNOFILE_ERROR;
    }
    *newseekp = newseek;
    return YUNOFILE_SUCCESS;
  }
}

