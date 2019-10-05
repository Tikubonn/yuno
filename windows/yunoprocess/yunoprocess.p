#include <windows.h>

typedef struct yunoprocess {
	yunoprocess_entry_point entrypoint;
	void *parameter;
	//yunoshared_memory **sharedmemoryp;
	struct  yunoshared_memory **sharedmemoryp;
	HANDLE process;
	HANDLE thread;
	HANDLE remotethread;
} yunoprocess;
