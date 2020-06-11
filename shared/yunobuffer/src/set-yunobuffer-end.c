#include <yuno.h>

inline int set_yunobuffer_end (yunosize offset, yunobuffer *buffer){
	if (offset < buffer->size){
		buffer->seekend = offset;
		return 0;
	}
	return 1;
}
