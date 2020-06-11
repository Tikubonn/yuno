#include <windows.h>

extern int __stdcall __free_yunoprocess (yunoprocess*, yunomemory**);

#define free_yunoprocess(process)\
__free_yunoprocess(process, &global_yunomemory)
