#include <yuno.h>

int new_yunopipe (int flags, yunosize inputbuffersize, yunosize outputbuffersize, yunofile **inputfilep, yunofile **outputfilep){
	yunofile *inputfile = allocate_yunomemory(sizeof(yunofile));
	if (inputfile == NULL){
		return 1;
	}
	yunofile *outputfile = allocate_yunomemory(sizeof(yunofile));
	if (outputfile == NULL){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(inputfile, sizeof(yunofile));
		set_yunoerror(lasterror);
		return 1;
	}
	void *inputbuffer = allocate_yunomemory(inputbuffersize);
	if (inputbuffer == NULL){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(inputfile, sizeof(yunofile));
		free_yunomemory(outputfile, sizeof(yunofile));
		set_yunoerror(lasterror);
		return 1;
	}
	void *outputbuffer = allocate_yunomemory(outputbuffersize);
	if (outputbuffer == NULL){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(inputfile, sizeof(yunofile));
		free_yunomemory(outputfile, sizeof(yunofile));
		free_yunomemory(inputbuffer, inputbuffersize);
		set_yunoerror(lasterror);
		return 1;
	}
	if (make_yunopipe(flags, inputbuffer, inputbuffersize, outputbuffer, outputbuffersize, inputfile, outputfile) != 0){
		yunoerror lasterror = get_yunoerror();
		free_yunomemory(inputfile, sizeof(yunofile));
		free_yunomemory(outputfile, sizeof(yunofile));
		free_yunomemory(inputbuffer, inputbuffersize);
		free_yunomemory(outputbuffer, outputbuffersize);
		set_yunoerror(lasterror);
		return 1;
	}
	*inputfilep = inputfile;
	*outputfilep = outputfile;
	return 0;
}
