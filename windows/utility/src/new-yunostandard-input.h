#include <windows.h>
#include <stdbool.h>

extern yunofile *__stdcall __new_yunostandard_input (bool, yunosize, yunomemory**);

#define new_yunostandard_input(asyncp, buffersize)\
__new_yunostandard_input(asyncp, buffersize, &global_yunomemory)
