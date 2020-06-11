#include <windows.h>

extern void *__stdcall __allocate_yunoshared_memory (yunosize, yunomemory**, yunoshared_memory**);

#define allocate_yunoshared_memory(size)\
__allocate_yunoshared_memory(size, &global_yunomemory, &global_yunoshared_memory)
