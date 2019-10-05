#include <yuno.private>
#include <sys/types.h>
#include <signal.h>

yunoprocess_status __yunocall start_yunoprocess (yunoprocess *process){
  if (kill(process->processid, SIGCONT) != 0){
    return YUNOPROCESS_ERROR;
  }
  return YUNOPROCESS_SUCCESS;
}

