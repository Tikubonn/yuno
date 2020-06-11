#include <yuno.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

static int parse_flags (int flags, bool *asyncp, int *flagsp){
	reset_yunoerror();
	int asyncflags = flags & (YUNOFILE_SYNC | YUNOFILE_ASYNC);
	switch (asyncflags){
		case 0:
			*asyncp = false;
			break;
		case YUNOFILE_SYNC:
			*asyncp = false;
			break;
		case YUNOFILE_ASYNC:
			*asyncp = true;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	int fileflags = flags & ~(YUNOFILE_SYNC | YUNOFILE_ASYNC);
	switch (fileflags){
    case YUNOFILE_READABLE:
      *flagsp = O_RDONLY;
      return 0;
    case YUNOFILE_WRITABLE:
      *flagsp = O_WRONLY | O_CREAT | O_TRUNC;
      return 0;
    case YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE:
      *flagsp = O_WRONLY | O_CREAT | O_TRUNC;
      return 0;
    case YUNOFILE_WRITABLE | YUNOFILE_APPEND:
      *flagsp = O_WRONLY | O_CREAT | O_APPEND;
      return 0;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE:
      *flagsp = O_RDWR | O_CREAT | O_TRUNC;
      return 0;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE:
      *flagsp = O_RDWR | O_CREAT | O_TRUNC;
      return 0;
    case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_APPEND:
      *flagsp = O_RDWR | O_CREAT | O_APPEND;
      return 0;
    default:
	    set_yunoerror(YUNOARGUMENT_ERROR);
      return 1;
  }
}

#define DEFAULT_PERMISSION (S_IRWXU | S_IRWXG | S_IROTH)

int open_yunofile (const char *filename, int flags, void *bufferseq, yunosize buffersize, yunofile *file){
	reset_yunoerror();
	bool asyncp;
	int linuxflags;
	if (parse_flags(flags, &asyncp, &linuxflags) != 0){
		return 1;
	}
	int filefd = open(filename, linuxflags, DEFAULT_PERMISSION);
	if (filefd == -1){
		switch (errno){
			case EACCES:
				set_yunoerror(YUNOPERMISSION_ERROR);
				return 1;
			case EISDIR:
				set_yunoerror(YUNOIS_A_DIRECTORY);
				return 1;
			case ENOENT:
				set_yunoerror(YUNODOES_NOT_EXIST);
				return 1;
			default:
				set_yunoerror(YUNOOS_ERROR);
				return 1;
		}
	}
	init_yunofile(filefd, flags, asyncp, bufferseq, buffersize, file);
	return 0;
}
