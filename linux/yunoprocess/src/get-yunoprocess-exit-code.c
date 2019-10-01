#include <yuno.private>
#include <sys/types.h>
#include <sys/wait.h>

yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess *process, int *exitcodep){
  int status;
  pid_t pid = waitpid(process->processid, &status, WNOHANG);
  if (pid == -1){
    return YUNOPROCESS_ERROR;
  }
  else
  if (pid == 0){
    return YUNOPROCESS_BUSY;
  }
  else {
    if (WIFEXITED(status)){
      *exitcodep = WEXITSTATUS(status);
      return YUNOPROCESS_SUCCESS;
    }
    else {
      return YUNOPROCESS_BUSY;
    }
  }
}

