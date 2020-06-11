#include <yuno.h>
#include <errno.h>
#include <unistd.h>

int yunosleep (yunoseconds seconds, yunoseconds milliseconds){
  reset_yunoerror();
  if (usleep(milliseconds * 1000) != 0){
  	switch (errno){
  		case EINVAL:
  			set_yunoerror(YUNOARGUMENT_ERROR);
  			return 1;
  		default:
  			set_yunoerror(YUNOOS_ERROR);
  			return 1;
  	}
  }
  if (sleep(seconds) != 0){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
  }
  return 0;
}
