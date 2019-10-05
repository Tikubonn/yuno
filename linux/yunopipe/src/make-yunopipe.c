#include <yuno.private>
#include <stdlib.h>

yunopipe_status __yunocall make_yunopipe (yunofile **inputp, yunofile **outputp){
  yunofile *input = malloc(sizeof(yunofile));
  if (input == NULL){
    return YUNOPIPE_ERROR;
  }
  yunofile *output = malloc(sizeof(yunofile));
  if (output == NULL){
    free(input);
    return YUNOPIPE_ERROR;
  }
  if (make_yunopipe_manually(input, output) != YUNOPIPE_SUCCESS){
    free(input);
    free(output);
    return YUNOPIPE_ERROR;
  }
  *inputp = input;
  *outputp = output;
  return YUNOPIPE_SUCCESS;
}

