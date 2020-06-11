#include <yuno.h>
#include <windows.h>
#include <stddef.h>

static inline void clear (void *sequence, size_t size){
	for (size_t index = 0; index < size; index++){
		((char*)sequence)[index] = 0;
	}
}

inline void setup_yunofile_overlapped (yunosize seek, HANDLE event, OVERLAPPED *overlappedp){
	clear(overlappedp, sizeof(OVERLAPPED));
	LARGE_INTEGER position;
	position.QuadPart = seek;
	overlappedp->Offset = position.LowPart;
	overlappedp->OffsetHigh = position.HighPart;
	overlappedp->hEvent = event;
}
