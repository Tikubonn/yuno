#include <yuno.private>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

yunofile_status __yunocall open_yunofile_manually (const char *filename, int mode, void *bufferseq, yunosize buffersize, yunofile *file){
  int flags;
  switch (mode){
    case YUNOFILE_READABLE:
      flags = O_RDONLY;
      break;
    case YUNOFILE_WRITABLE:
      flags = O_WRONLY | O_CREAT;
      break;
    case YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE:
      flags = O_WRONLY | O_CREAT | O_TRUNC;
      break;
    case YUNOFILE_WRITABLE | YUNOFILE_APPEND:
      flags = O_WRONLY | O_CREAT | O_APPEND;
      break;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE:
      flags = O_RDWR | O_CREAT;
      break;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE:
      flags = O_RDWR | O_CREAT | O_TRUNC;
      break;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_APPEND:
      flags = O_RDWR | O_CREAT | O_APPEND;
      break;
    default:
      return YUNOFILE_ERROR; // unknown combination!
  }
  /*
  switch (mode){
    case YUNOFILE_READABLE:
      flags = O_RDONLY;
      break;
    case YUNOFILE_WRITABLE:
      flags = O_WRONLY | O_CREAT | O_TRUNC;
      break;
    case YUNOFILE_APPENDABLE:
      flags = O_WRONLY | O_CREAT | O_APPEND;
      break;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE:
      flags = O_RDWR | O_CREAT | O_TRUNC;
      break;
    case YUNOFILE_READABLE | YUNOFILE_APPENDABLE:
      flags = O_RDWR | O_CREAT | O_APPEND;
      break;
    default:
      return YUNOFILE_ERROR;
  }
  */
  int fd = open(filename, flags, S_IRUSR | S_IWUSR | S_IRWXG | S_IRGRP | S_IROTH | S_IWOTH);
  if (fd == -1){
    switch (errno){
      case ENOENT:
        return YUNOFILE_DOES_NOT_EXIST;
      default:
        return YUNOFILE_ERROR;
    }
  }
  init_yunofile(fd, mode, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

