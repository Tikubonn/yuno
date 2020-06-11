#include <yuno.h>

inline void clear_yunobuffer (yunobuffer *buffer){
	buffer->seek = 0;
	buffer->seekend = 0;
}
