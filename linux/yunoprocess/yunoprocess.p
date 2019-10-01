#include <sys/types.h>

typedef struct yunoprocess {
  yunoprocess_entry_point entrypoint;
  void *parameter;
  pid_t processid;
} yunoprocess;

