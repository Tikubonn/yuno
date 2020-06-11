#include <windows.h>
#include <stdbool.h>

extern yunofile *__stdcall __new_yunostandard_output (bool, yunosize, yunomemory**);

#define new_yunostandard_output(asyncp, buffersize)\
__new_yunostandard_output(asyncp, buffersize, &global_yunomemory)
