#include <yuno.h>
#include <unistd.h>
#include <stdbool.h>

static int parse_flags (int flags, bool *asyncp){
	switch (flags){
		case 0:
			*asyncp = false;
			return 0;
		case YUNOFILE_SYNC:
			*asyncp = false;
			return 0;
		case YUNOFILE_ASYNC:
			*asyncp = true;
			return 0;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
}

int make_yunopipe (int flags, void *inputbufferseq, yunosize inputbuffersize, void *outputbufferseq, yunosize outputbuffersize, yunofile *inputfilep, yunofile *outputfilep){
	reset_yunoerror();
	bool asyncp;
	if (parse_flags(flags, &asyncp) != 0){
		return 1;
	}
  int pipefds[2];
  if (pipe(pipefds) == -1){
    set_yunoerror(YUNOOS_ERROR);
    return 1;
  }
  init_yunofile(pipefds[0], YUNOFILE_READABLE, asyncp, inputbufferseq, inputbuffersize, inputfilep);
  init_yunofile(pipefds[1], YUNOFILE_WRITABLE, asyncp, outputbufferseq, outputbuffersize, outputfilep);
  return 0;
}
