#include <yuno.h>
#include <windows.h>

int __stdcall __new_yunopipe (int flags, yunosize inputbuffersize, yunosize outputbuffersize, yunofile **inputfilep, yunofile **outputfilep, yunomemory **globalmemoryp){
	yunofile *inputfile = __allocate_yunomemory(sizeof(yunofile), globalmemoryp);
	if (inputfile == NULL){
		return 1;
	}
	yunofile *outputfile = __allocate_yunomemory(sizeof(yunofile), globalmemoryp);
	if (outputfile == NULL){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(inputfile, sizeof(yunofile), globalmemoryp);
		set_yunoerror(lasterror);
		return 1;
	}
	void *inputbuffer = __allocate_yunomemory(inputbuffersize, globalmemoryp);
	if (inputbuffer == NULL){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(inputfile, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(outputfile, sizeof(yunofile), globalmemoryp);
		set_yunoerror(lasterror);
		return 1;
	}
	void *outputbuffer = __allocate_yunomemory(outputbuffersize, globalmemoryp);
	if (outputbuffer == NULL){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(inputfile, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(outputfile, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(inputbuffer, inputbuffersize, globalmemoryp);
		set_yunoerror(lasterror);
		return 1;
	}
	if (make_yunopipe(flags, inputbuffer, inputbuffersize, outputbuffer, outputbuffersize, inputfile, outputfile) != 0){
		yunoerror lasterror = get_yunoerror();
		__free_yunomemory(inputfile, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(outputfile, sizeof(yunofile), globalmemoryp);
		__free_yunomemory(inputbuffer, inputbuffersize, globalmemoryp);
		__free_yunomemory(outputbuffer, outputbuffersize, globalmemoryp);
		set_yunoerror(lasterror);
		return 1;
	}
	*inputfilep = inputfile;
	*outputfilep = outputfile;
	return 0;
}
