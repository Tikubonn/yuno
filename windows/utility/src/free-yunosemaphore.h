#include <windows.h>

extern int __stdcall __free_yunosemaphore (yunosemaphore*, yunomemory**);

#define free_yunosemaphore(semaphore)\
__free_yunosemaphore(semaphore, &global_yunomemory)
