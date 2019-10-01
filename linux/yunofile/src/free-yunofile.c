#include <yuno.private>
#include <stdlib.h>

yunofile_status __yunocall free_yunofile (yunofile *file){
  void *bufferseq = yunofile_buffer_array(&(file->buffer));
  if (bufferseq != NULL){
    free(bufferseq);
  }
  free(file);
  return YUNOFILE_SUCCESS;
}

