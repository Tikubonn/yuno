#include <windows.h>

extern int __stdcall __make_yunoprocess (yunoentrypoint, void*, yunomemory**, yunoshared_memory**, yunoprocess*);

#define make_yunoprocess(entrypoint, parameter, processp)\
__make_yunoprocess(entrypoint, parameter, &global_yunomemory, &global_yunoshared_memory, processp)
