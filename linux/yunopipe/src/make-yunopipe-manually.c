#include <yuno.private>
#include <unistd.h>

yunopipe_status __yunocall make_yunopipe_manually (
	void *inputbufferseq,
	yunosize inputbuffersize,
	void *outputbufferseq,
	yunosize outputbuffersize, 
	yunofile *inputp,
	yunofile *outputp){
  int pipefds[2];
  if (pipe(pipefds) == -1){
    return YUNOPIPE_ERROR;
  }
  init_yunofile(pipefds[0], YUNOFILE_READABLE, inputbufferseq, inputbuffersize, inputp);
  init_yunofile(pipefds[1], YUNOFILE_WRITABLE, outputbufferseq, outputbuffersize, outputp);
  return YUNOPIPE_SUCCESS;
}
