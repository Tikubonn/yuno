#include <stdint.h>

#define YUNOPIPE_PATH_PREFIX "\\\\.\\pipe\\yunopipe"
#define YUNOPIPE_INPUT_BUFFER_SIZE 4096
#define YUNOPIPE_OUTPUT_BUFFER_SIZE 4096
#define YUNOPIPE_TRY_COUNT 65536

uintmax_t global_yunopipe_path_counter;
