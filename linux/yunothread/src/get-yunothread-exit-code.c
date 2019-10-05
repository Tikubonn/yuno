#include <yuno.private>
#include <sys/wait.h>
#include <unistd.h>

yunothread_status __yunocall get_yunothread_exit_code (yunothread *thread, int *exitcodep){
  if (thread->exitedp == true){
    *exitcodep = thread->exitcode;
    return YUNOTHREAD_SUCCESS;
  }
  return YUNOTHREAD_BUSY;
}

