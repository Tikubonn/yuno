#include <windows.h>

extern int __stdcall __sync_yunoshared_memory (void*, yunoshared_memory**);

#define sync_yunoshared_memory(address)\
__sync_yunoshared_memory(address, &global_yunoshared_memory)
