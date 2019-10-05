#include <yuno.private>
#include <sys/types.h>
#include <sys/wait.h>

yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess *process, int *exitcodep){
  if (process->exitedp == true){
    *exitcodep = process->exitcode;
    return YUNOPROCESS_SUCCESS;
  }
  return YUNOPROCESS_BUSY;
}

