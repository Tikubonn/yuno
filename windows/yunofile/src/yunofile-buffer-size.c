#include <yuno.h>

inline yunosize yunofile_buffer_size (yunofile *file){
	return yunobuffer_size(&(file->asyncbuffer));
}
