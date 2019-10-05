#include <yuno.private>
#include <aio.h>
#include <time.h>
#include <errno.h>

static void copy_from_buffer (void *sequence, yunosize size, yunofile_buffer *buffer){
  void *bufferseq = yunofile_buffer_array(buffer);
  for (yunosize index = 0; index < size; index++){
    ((char*)sequence)[index] = 
      ((char*)(bufferseq))[index];
  }
}

yunofile_status __yunocall wait_read_yunofile (void *sequence, yunofile_wait_mode waitmode, yunofile *file, yunosize *readsizep){
  if (file->asyncp == true){
    if (file->requeststatus != YUNOFILE_READING){
      return YUNOFILE_ERROR;
    }
    struct timespec time;
    struct timespec *timep;
    switch (waitmode){
      case YUNOFILE_FOREVER:
        timep = NULL;
        break;
      case YUNOFILE_NOWAIT:
        time.tv_sec = 0;
        time.tv_nsec = 0;
        timep = &time;
        break;
      default:
        return YUNOFILE_ERROR;
    }
    struct aiocb const *cbs[] = { &(file->cb) };
    if (aio_suspend(cbs, 1, timep) == -1){
      switch (errno){
        case EAGAIN:
          return YUNOFILE_BUSY;
        default:
          return YUNOFILE_ERROR;
      }
    }
    switch (aio_error(&(file->cb))){
      case 0: {
        ssize_t readsize = aio_return(&(file->cb));
        if (readsize < 0){
          return YUNOFILE_ERROR;
        }
        copy_from_buffer(sequence, readsize, &(file->buffer));
        file->requeststatus = YUNOFILE_FREE;
        file->asyncseek += readsize;
        *readsizep = readsize;
        return YUNOFILE_SUCCESS;
      }
      case EINPROGRESS: {
        return YUNOFILE_BUSY;
      }
      default: {
        return YUNOFILE_ERROR;
      }
    }
  }
  else {
    if (file->requeststatus != YUNOFILE_READ_COMPLETED){
      return YUNOFILE_ERROR;
    }
    copy_from_buffer(sequence, file->completedsize, &(file->buffer));
    file->requeststatus = YUNOFILE_FREE;
    *readsizep = file->completedsize;
    return YUNOFILE_SUCCESS;
  }
}

