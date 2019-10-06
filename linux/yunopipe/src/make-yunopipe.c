#include <yuno.private>
#include <stdlib.h>

yunopipe_status __yunocall make_yunopipe (
	yunosize inputbuffersize,
	yunosize outputbuffersize,
	yunofile **inputp,
	yunofile **outputp){
  yunofile *input = malloc(sizeof(yunofile));
  if (input == NULL){
    return YUNOPIPE_ERROR;
  }
  yunofile *output = malloc(sizeof(yunofile));
  if (output == NULL){
    free(input);
    return YUNOPIPE_ERROR;
  }
	void *inputbufferseq = NULL;
	if (0 < inputbuffersize){
		inputbufferseq = malloc(inputbuffersize);
		if (inputbufferseq == NULL){
			free(input);
			free(output);
			return NULL;
		}
	}
	void *outputbufferseq = NULL;
	if (0 < outputbuffersize){
		outputbufferseq = malloc(outputbuffersize);
		if (outputbufferseq == NULL){
			free(input);
			free(output);
			free(inputbufferseq);
			return NULL;
		}
	}
  if (make_yunopipe_manually(
		inputbufferseq,
		inputbuffersize,
		outputbufferseq,
		outputbuffersize,
		input,
		output) != YUNOPIPE_SUCCESS){
    free(input);
    free(output);
    free(inputbufferseq);
    free(outputbufferseq);
    return YUNOPIPE_ERROR;
  }
  *inputp = input;
  *outputp = output;
  return YUNOPIPE_SUCCESS;
}

