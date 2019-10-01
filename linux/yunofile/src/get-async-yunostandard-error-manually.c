#include <yuno.private>

yunofile_status __yunocall get_async_yunostandard_error_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_async_yunofile(2, YUNOFILE_READABLE, 0, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

