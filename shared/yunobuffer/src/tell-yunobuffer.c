#include <yuno.h>

inline yunosize tell_yunobuffer (yunobuffer *buffer){
	return buffer->seek;
}
