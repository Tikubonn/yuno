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

int open_yunostandard_output (int flags, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	bool asyncp;
	if (parse_flags(flags, &asyncp) != 0){
		return 1;
	}
	int dupped = dup(1);
	if (dupped == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	init_yunofile(dupped, YUNOFILE_WRITABLE, asyncp, bufferseq, buffersize, file);
	return 0;
}
