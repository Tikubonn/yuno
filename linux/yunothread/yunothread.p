#include <stdbool.h>

typedef struct yunothread {
	pthread_t thread;
	yunoentrypoint entrypoint;
	void *parameter;
	bool exitedp;
	int exitcode;
	bool closedp;
} yunothread;
