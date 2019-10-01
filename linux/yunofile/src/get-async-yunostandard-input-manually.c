#include <yuno.private>

yunofile_status __yunocall get_async_yunostandard_input_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_async_yunofile(0, YUNOFILE_READABLE, 0, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

