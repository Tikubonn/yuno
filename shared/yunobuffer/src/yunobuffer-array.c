#include <yuno.h>

inline void *yunobuffer_array (yunobuffer *buffer){
	return buffer->sequence;
}
