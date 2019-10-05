#include <yuno.private>
#include <unistd.h>

yunopipe_status __yunocall make_yunopipe_manually (yunofile *inputp, yunofile *outputp){
  int pipefds[2];
  if (pipe(pipefds) == -1){
    return YUNOPIPE_ERROR;
  }
  init_yunofile(pipefds[0], YUNOFILE_READABLE, NULL, 0, inputp);
  init_yunofile(pipefds[1], YUNOFILE_WRITABLE, NULL, 0, outputp);
  return YUNOPIPE_SUCCESS;
}

