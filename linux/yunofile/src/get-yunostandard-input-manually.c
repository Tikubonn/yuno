#include <yuno.private>

yunofile_status __yunocall get_yunostandard_input_manually (void *bufferseq, yunosize buffersize, yunofile *file){
  init_yunofile(0, YUNOFILE_READABLE, bufferseq, buffersize, file);
  return YUNOFILE_SUCCESS;
}

