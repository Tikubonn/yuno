#include <yuno.private>
#include <windows.h>

static void clear (void *sequence, size_t size){
	for (size_t index = 0; index < size; index++){
		((char*)sequence)[index] = 0;
	}
}

void setup_yunofile_overlapped (yunosize seek, OVERLAPPED *overlappedp){
	clear(overlappedp, sizeof(OVERLAPPED));
	LARGE_INTEGER position;
	position.QuadPart = seek;
	overlappedp->Offset = position.LowPart;
	overlappedp->OffsetHigh = position.HighPart;
	overlappedp->hEvent = NULL; //! you can redefine here if you want.
}
