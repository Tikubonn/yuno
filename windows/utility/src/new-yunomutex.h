#include <windows.h>

extern yunomutex *__stdcall __new_yunomutex (yunomemory**);

#define new_yunomutex()\
__new_yunomutex(&global_yunomemory)
