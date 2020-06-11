#include <windows.h>
#include <stdbool.h>

extern int __stdcall __new_yunopipe (int, yunosize, yunosize, yunofile**, yunofile**, yunomemory**);

#define new_yunopipe(mode, inputbuffersize, outputbuffersize, inputfilep, outputfilep)\
__new_yunopipe(mode, inputbuffersize, outputbuffersize, inputfilep, outputfilep, &global_yunomemory)
