
typedef struct yunothread {
  yunothread_entry_point entrypoint;
  void *parameter;
  void *childstack;
  int processid;
} yunothread;
 
