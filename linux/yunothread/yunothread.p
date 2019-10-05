#include <stdbool.h>

typedef struct yunothread {
  yunothread_entry_point entrypoint;
  void *parameter;
  void *childstack;
  int processid;
  bool exitedp;
  int exitcode;
} yunothread;
 
