#include <yuno.h>

inline int seek_yunobuffer (yunossize distance, yunobuffer_whence whence, yunobuffer *buffer, yunosize *newoffsetp){
	switch (whence){
		case YUNOBUFFER_BEGIN: {
			if ((yunosize)distance < buffer->size){
				buffer->seek = distance;
				*newoffsetp = distance;
				return 0;
			}
			return 1;
		}
		case YUNOBUFFER_CURRENT: {
			yunosize newoffset = buffer->seek + distance;
			if (newoffset < buffer->size){
				buffer->seek = newoffset;
				*newoffsetp = newoffset;
				return 0;
			}
			return 1;
		}
		case YUNOBUFFER_END: {
			yunosize newoffset = buffer->seekend + distance;
			if (newoffset < buffer->size){
				buffer->seek = newoffset;
				*newoffsetp = newoffset;
				return 0;
			}
			return 1;
		}
		default: {
			return 1;
		}
	}
}
