#include <windows.h>
#include <stdbool.h>

typedef struct yunoprocess {
	void *parameter;
	yunoentrypoint entrypoint;
	HANDLE process;
	HANDLE thread;
	HANDLE remotethread;
	bool closedp;
} yunoprocess;
