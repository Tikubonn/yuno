#include <yuno.private>
#include <stdio.h>

yunopipe_status __yunocall make_yunopipe (
	yunosize inputbuffersize,
	yunosize outputbuffersize,
	yunofile **inputfilep,
	yunofile **outputfilep){
	yunofile *inputfile = malloc(sizeof(yunofile));
	if (inputfile == NULL){
		return YUNOPIPE_ERROR;
	}
	yunofile *outputfile = malloc(sizeof(yunofile));
	if (outputfile == NULL){
		free(inputfile);
		return YUNOPIPE_ERROR;
	}
	void *inputbufferseq = NULL;
	if (0 < inputbuffersize){
		inputbufferseq = malloc(inputbuffersize);
		if (inputbufferseq == NULL){
			free(inputfile);
			free(outputfile);
			return YUNOPIPE_ERROR;
		}
	}
	void *outputbufferseq = NULL;
	if (0 < outputbuffersize){
		outputbufferseq = malloc(outputbuffersize);
		if (outputbufferseq == NULL){
			free(inputfile);
			free(outputfile);
			free(inputbufferseq);
			return YUNOPIPE_ERROR;
		}
	}
	if (make_yunopipe_manually(
		inputbufferseq,
		inputbuffersize,
		outputbufferseq,
		outputbuffersize,
		inputfile,
		outputfile) != YUNOPIPE_SUCCESS){
		free(inputfile);
		free(outputfile);
		free(inputbufferseq);
		free(outputbufferseq);
		return YUNOPIPE_ERROR;
	}
	*inputfilep = inputfile;
	*outputfilep = outputfile;
	return YUNOPIPE_SUCCESS;
}
