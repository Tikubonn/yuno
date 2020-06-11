#include <windows.h>

extern int __stdcall __free_yunomemory (void*, yunosize, yunomemory**);

#define free_yunomemory(address, size)\
__free_yunomemory(address, size, &global_yunomemory)
