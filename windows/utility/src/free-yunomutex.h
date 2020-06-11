#include <windows.h>

extern int __stdcall __free_yunomutex (yunomutex*, yunomemory**);

#define free_yunomutex(mutex)\
__free_yunomutex(mutex, &global_yunomemory)
