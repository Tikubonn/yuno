#include <yuno.private>
#include <stdlib.h>

yunofile __yunocall *get_async_yunostandard_output (yunosize buffersize){
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
  if (get_async_yunostandard_output_manually(bufferseq, buffersize, file) != YUNOFILE_SUCCESS){
    free(file);
    free(bufferseq);
    return NULL;
  }
  return file;
}

