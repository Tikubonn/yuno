#include <yuno.private>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static int wait_process (){
  pid_t pid = getpid();
  if (kill(pid, SIGSTOP) != 0){
    return 1;
  }
  return 0;
}

static void __subprocess_main (yunoprocess *process){
  if (wait_process()){
    _exit(1); // abort process!
  }
  int exitcode = process->entrypoint(process->parameter);
  _exit(exitcode); // exit process!
}

yunoprocess_status __yunocall make_yunoprocess_manually (yunoprocess_entry_point entrypoint, void *parameter, yunoprocess *process){
  process->entrypoint = entrypoint;
  process->parameter = parameter;
  pid_t pid = fork();
  if (pid == -1){
    return YUNOPROCESS_ERROR;
  }
  else 
  if (pid == 0){
    __subprocess_main(process);
    return YUNOPROCESS_ERROR;
  }
  else {
    int status;
    pid_t pid2 = waitpid(pid, &status, WUNTRACED);
    if (pid2 < 0){
      return YUNOPROCESS_ERROR;
    }
    else
    if (pid2 == 0){
      return YUNOPROCESS_ERROR;
    }
    else {
      if (WIFSTOPPED(status)){
        process->processid = pid;
        process->exitedp = false;
        process->exitcode = 0; //! can be undefined.
        return YUNOPROCESS_SUCCESS;
      }
      return YUNOPROCESS_ERROR;
    }
  }
}

