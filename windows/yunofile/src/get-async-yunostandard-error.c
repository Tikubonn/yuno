#include <yuno.private>
#include <stdlib.h>

yunofile __yunocall *get_async_yunostandard_error (yunosize buffersize){
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
	if (get_async_yunostandard_error_manually(bufferseq, buffersize, file) != YUNOFILE_SUCCESS){
		free(file);
		free(bufferseq);
		return NULL;
	}
	return file;
}
