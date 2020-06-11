#include <windows.h>

extern int __stdcall __free_yunofile (yunofile*, yunomemory**);

#define free_yunofile(file)\
__free_yunofile(file, &global_yunomemory)
