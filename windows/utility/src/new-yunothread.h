#include <windows.h>

extern yunothread *__stdcall __new_yunothread (yunoentrypoint, void*, yunomemory**);

#define new_yunothread(entrypoint, parameter)\
__new_yunothread(entrypoint, parameter, &global_yunomemory)
