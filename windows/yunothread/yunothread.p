#include <windows.h>
#include <stdbool.h>

typedef struct yunothread {
	void *parameter;
	yunoentrypoint entrypoint;
	HANDLE thread;
	bool closedp;
} yunothread;
