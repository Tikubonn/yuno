#include <windows.h>

extern yunoprocess *__stdcall __new_yunoprocess (yunoentrypoint, void*, yunomemory**, yunoshared_memory**);

#define new_yunoprocess(entrypoint, parameter)\
__new_yunoprocess(entrypoint, parameter, &global_yunomemory, &global_yunoshared_memory)
