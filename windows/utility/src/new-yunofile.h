#include <windows.h>

extern yunofile *__stdcall __new_yunofile (const char*, int, yunosize, yunomemory**);

#define new_yunofile(filename, mode, buffersize)\
__new_yunofile(filename, mode, buffersize, &global_yunomemory)
