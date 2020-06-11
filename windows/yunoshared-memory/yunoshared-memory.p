#include <windows.h>

typedef struct yunoshared_memory {
	DWORD processid;
	HANDLE mappingfile;
	void *mappingaddress;
	yunosize mappingsize;
	yunoallocator allocator;
	struct yunoshared_memory *next;
} yunoshared_memory;

yunoshared_memory *global_yunoshared_memory;
