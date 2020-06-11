#include <windows.h>
#include <stdbool.h>

extern yunofile *__stdcall __new_yunostandard_error (bool, yunosize, yunomemory**);

#define new_yunostandard_error(asyncp, buffersize)\
__new_yunostandard_error(asyncp, buffersize, &global_yunomemory)
