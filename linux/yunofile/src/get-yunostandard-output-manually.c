#include <yuno.private>

yunofile_status __yunocall get_yunostandard_output_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_yunofile(1, YUNOFILE_WRITABLE, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

