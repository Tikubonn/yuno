#include <yuno.private>
#include <stdlib.h>

yunopipe_status __yunocall (yunofile **inputp, yunofile **outputp){
  yunofile *input = malloc(sizeof(yunofile));
  if (input == NULL){
    return NULL;
  }
  yunofile *output = malloc(sizeof(yunofile));
  if (output == NULL){
    free(input);
    return NULL;
  }
  *inputp = input;
  *outputp = output;
  return YUNOPIPE_SUCCESS;
}

