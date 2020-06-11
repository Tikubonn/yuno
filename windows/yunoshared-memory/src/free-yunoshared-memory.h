#include <windows.h>

extern int __stdcall __free_yunoshared_memory (void*, yunosize, yunomemory**, yunoshared_memory**);

#define free_yunoshared_memory(address, size)\
__free_yunoshared_memory(address, size, &global_yunomemory, &global_yunoshared_memory)
