#include <windows.h>

typedef struct yunoprocess {
	yunoprocess_entry_point entrypoint;
	void *parameter;
	HANDLE process;
	HANDLE thread;
	HANDLE remotethread;
} yunoprocess;
