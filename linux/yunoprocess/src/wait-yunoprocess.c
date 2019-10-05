#include <yuno.private>
#include <sys/types.h>
#include <sys/wait.h>

yunoprocess_status __yunocall wait_yunoprocess (yunoprocess_wait_mode waitmode, yunoprocess *process){
  if (process->exitedp == false){
    int option;
    switch (waitmode){
      case YUNOPROCESS_FOREVER:
        option = 0;
        break;
      case YUNOPROCESS_NOWAIT:
        option = WNOHANG;
        break;
      default:
        return YUNOPROCESS_ERROR;
    }
    int status;
    pid_t pid = waitpid(process->processid, &status, option);
    if (pid == -1){
      return YUNOPROCESS_ERROR;
    }
    else
    if (pid == 0){
      return YUNOPROCESS_BUSY;
    }
    else {
      if (WIFEXITED(status)){
        process->exitedp = true;
        process->exitcode = WEXITSTATUS(status);
        return YUNOPROCESS_SUCCESS;
      }
      return YUNOPROCESS_BUSY;
    }
  }
  return YUNOPROCESS_SUCCESS;
}

