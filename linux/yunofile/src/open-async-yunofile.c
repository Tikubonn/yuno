#include <yuno.private>
#include <stdlib.h>

yunofile __yunocall *open_async_yunofile (const char *filename, int mode, yunosize buffersize){
  yunofile *file = malloc(sizeof(yunofile));
  if (file == NULL){
    return NULL;
  }
  void *bufferseq = NULL;
  if (0 < buffersize){
    bufferseq = malloc(buffersize);
    if (bufferseq == NULL){
      free(file);
      return NULL;
    }
  }
  if (open_async_yunofile_manually(filename, mode, bufferseq, buffersize, file) != YUNOFILE_SUCCESS){
    free(file);
    free(bufferseq);
    return NULL;
  }
  return file;
}

