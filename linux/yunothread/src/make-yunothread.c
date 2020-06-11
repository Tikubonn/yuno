#include <yuno.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

static void *entrypoint_wrapper (void *parameter){
  reset_yunoerror();
  yunothread *thread = parameter;
  pthread_t pthread = pthread_self();
  if (pthread_kill(pthread, SIGSTOP) != 0){
    set_yunoerror(YUNOOS_ERROR);
    return (void*)1;
  }
  int exitcode = thread->entrypoint(thread->parameter);
  thread->exitcode = exitcode;
  return (void*)0;
}

int make_yunothread (yunoentrypoint entrypoint, void *parameter, yunothread *thread){
  thread->entrypoint = entrypoint;
  thread->parameter = parameter;
  thread->exitedp = false;
  thread->exitcode = -1;
  thread->closedp = false;
  pthread_t pthread;
  if (pthread_create(&pthread, NULL, entrypoint_wrapper, thread) != 0){
    return 1;
  }
  thread->thread = pthread;
  return 0;
}
