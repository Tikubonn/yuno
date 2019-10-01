#include <yuno.private>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

static int __wait_process (){
  pid_t pid = getpid();
  if (kill(pid, SIGSTOP) == -1){
    return 1;
  }
  return 0;
}

static void __subprocess_main (yunoprocess *process){
  if (__wait_process() != 0){
    _exit(1); // exit process!
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
    process->processid = pid;
    return YUNOPROCESS_SUCCESS;
  }
}

