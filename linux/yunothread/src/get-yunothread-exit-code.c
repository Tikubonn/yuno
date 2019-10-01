#include <yuno.private>
#include <sys/wait.h>
#include <unistd.h>

yunothread_status __yunocall get_yunothread_exit_code (yunothread *thread, int *exitcodep){
  int status;
  pid_t pid = waitpid(thread->processid, &status, WNOHANG);
  if (pid == -1){
    return YUNOTHREAD_ERROR;
  }
  if (pid == 0){
    return YUNOTHREAD_BUSY;
  }
  else {
    if (WIFEXITED(status)){
      *exitcodep = WEXITSTATUS(status);
      return YUNOTHREAD_SUCCESS;
    }
    else {
      return YUNOTHREAD_BUSY;
    }
  }
  /*
  int status;
  pid_t pid = waitpid(thread->processid, &status, WNOHANG | WIFEXITED);
  if (pid == -1){
    return YUNOTHREAD_ERROR;
  }
  else
  if (pid == 0){
    return YUNOTHREAD_BUSY;
  }
  else {
    int status;
    pid_t pid = waitpid(thread->processid, &status, WNOHANG | WEXITSTATUS);
    if (pid == -1){
      return YUNOTHREAD_ERROR;
    }
    else
    if (pid == 0){
      return YUNOTHREAD_BUSY;
    }
    else {
      *exitcodep = status;
      return YUNOTHREAD_SUCCESS;
    }
  }
  */
}

