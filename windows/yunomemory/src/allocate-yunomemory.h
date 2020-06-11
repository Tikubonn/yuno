#include <windows.h>

extern void *__stdcall __allocate_yunomemory (yunosize, yunomemory**);

#define allocate_yunomemory(size)\
__allocate_yunomemory(size, &global_yunomemory)
