#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

extern int __stdcall __make_yunopipe (int, void*, yunosize, void*, yunosize, yunofile*, yunofile*, uintmax_t*);

#define make_yunopipe(flags, inputbufferseq, inputbuffersize, outputbufferseq, outputbuffersize, inputfilep, outputfilep)\
__make_yunopipe(flags, inputbufferseq, inputbuffersize, outputbufferseq, outputbuffersize, inputfilep, outputfilep, &global_yunopipe_path_counter)
