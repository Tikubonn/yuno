#define _GNU_SOURCE
#include <sched.h>
#include <yuno.private>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <signal.h>

static pid_t __gettid (){
  return syscall(SYS_gettid);
}

static int __wait_thread (){
  pid_t threadid = __gettid();
  if (kill(threadid, SIGSTOP) == -1){
    return 1;
  }
  return 0;
}

static int __entry_point_wrapper (void *parameter){
  if (__wait_thread() != 0){
    return 1;
  }
  yunothread *thread = parameter;
  int exitcode = thread->entrypoint(thread->parameter);
  return exitcode;
}

#define YUNOTHREAD_CHILD_STACK_DEFAULT_SIZE 65536 

static int __get_child_stack_size (size_t *childstacksizep){
  struct rlimit rlim;
  if (getrlimit(RLIMIT_STACK, &rlim) == -1){
    return 1;
  }
  size_t childstacksize = YUNOTHREAD_CHILD_STACK_DEFAULT_SIZE;
  if (rlim.rlim_cur != RLIM_INFINITY){
    childstacksize = rlim.rlim_cur;
  }
  *childstacksizep = childstacksize;
  return 0;
}

yunothread_status __yunocall make_yunothread_manually (yunothread_entry_point entrypoint, void *parameter, yunothread *thread){
  size_t childstacksize;
  if (__get_child_stack_size(&childstacksize) != 0){
    return YUNOTHREAD_ERROR;
  }
  void *childstack = malloc(childstacksize);
  if (childstack == NULL){
    return YUNOTHREAD_ERROR;
  }
  thread->childstack = childstack;
  thread->entrypoint = entrypoint;
  thread->parameter = parameter;
  int processid = clone(
    __entry_point_wrapper, 
    childstack + childstacksize,
    CLONE_FILES | CLONE_VM | SIGCHLD,
    thread
  );
  if (processid == -1){
    free(childstack);
    return YUNOTHREAD_ERROR;
  }
  thread->processid = processid;
  return YUNOTHREAD_SUCCESS;
}

