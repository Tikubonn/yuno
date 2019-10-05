#include <sys/types.h>
#include <stdbool.h>

typedef struct yunoprocess {
  yunoprocess_entry_point entrypoint;
  void *parameter;
  pid_t processid;
  bool exitedp;
  int exitcode;
} yunoprocess;

