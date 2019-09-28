#include <yuno.private>
#include <stdlib.h>

yunofile __stdcall *open_yunofile (const char *filename, int mode, yunosize buffersize){
	yunofile *file = malloc(sizeof(yunofile));
	if (file == NULL){
		return NULL;
	}
	char *bufferseq = NULL;
	if (0 < buffersize){
		bufferseq = malloc(buffersize);
		if (bufferseq == NULL){
			free(file);
			return NULL;
		}
	}
	if (open_yunofile_manually(filename, mode, bufferseq, buffersize, file) != YUNOFILE_SUCCESS){
		free(file);
		free(bufferseq);
		return NULL;
	}
	return file;
}
