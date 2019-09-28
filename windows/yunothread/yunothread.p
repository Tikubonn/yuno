#include <windows.h>

typedef struct yunothread {
	yunothread_entry_point entrypoint;
	void *parameter;
	HANDLE thread;
} yunothread;
