#include <yuno.private>

yunofile_status __yunocall get_yunostandard_error_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_yunofile(2, YUNOFILE_WRITABLE, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

