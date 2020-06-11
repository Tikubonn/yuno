#include <yuno.h>
#include <windows.h>

extern int __stdcall __free_yunothread (yunothread*, yunomemory**);

#define free_yunothread(thread)\
__free_yunothread(thread, &global_yunomemory)
