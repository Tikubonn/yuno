#include <yuno.h>

inline void *yunofile_buffer_array (yunofile *file){
	return yunobuffer_array(&(file->asyncbuffer));
}
