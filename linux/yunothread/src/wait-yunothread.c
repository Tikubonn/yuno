#include <yuno.private>
#include <sys/types.h>
#include <sys/wait.h>

yunothread_status __yunocall wait_yunothread (yunothread_wait_mode waitmode, yunothread *thread){
  int option;
  switch (waitmode){
    case YUNOTHREAD_FOREVER:
      option = 0;
      break;
    case YUNOTHREAD_NOWAIT:
      option = WNOHANG;
      break;
    default:
      return YUNOTHREAD_ERROR;
  }
  int status;
  pid_t pid = waitpid(thread->processid, &status, option);
  if (pid == -1){
    return YUNOTHREAD_ERROR;
  }
  else 
  if (pid == 0){
    return YUNOTHREAD_BUSY;
  }
  else {
    if (WIFEXITED(status)){
      return YUNOTHREAD_SUCCESS;
    }
    return YUNOTHREAD_BUSY;
  }
}

