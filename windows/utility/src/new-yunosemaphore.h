#include <windows.h>

extern yunosemaphore *__stdcall __new_yunosemaphore (yunosize, yunomemory**);

#define new_yunosemaphore(maxcount)\
__new_yunosemaphore(maxcount, &global_yunomemory)
