#include <yuno.private>
#include <sys/types.h>
#include <signal.h>

yunothread_status __yunocall start_yunothread (yunothread *thread){
  if (kill(thread->processid, SIGCONT) == -1){
    return YUNOTHREAD_ERROR;
  }
  return YUNOTHREAD_SUCCESS;
}

