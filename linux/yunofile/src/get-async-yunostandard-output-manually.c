#include <yuno.private>

yunofile_status __yunocall get_async_yunostandard_output_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_async_yunofile(1, YUNOFILE_READABLE, 0, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

