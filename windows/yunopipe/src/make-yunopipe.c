#include <yuno.private>
#include <windows.h>
#include <stdio.h>

yunopipe_status __yunocall make_yunopipe (yunofile **inputfilep, yunofile **outputfilep){
	yunofile *inputfile = malloc(sizeof(yunofile));
	yunofile *outputfile = malloc(sizeof(yunofile));
	if (make_yunopipe_manually(inputfile, outputfile) != YUNOPIPE_SUCCESS){
		free(inputfile);
		free(outputfile);
		return YUNOPIPE_ERROR;
	}
	*inputfilep = inputfile;
	*outputfilep = outputfile;
	return YUNOPIPE_SUCCESS;
}
