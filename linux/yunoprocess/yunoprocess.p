#include <stdbool.h>

typedef struct yunoprocess {
	int processid;
	yunoentrypoint entrypoint;
	void *parameter;
	bool exitedp;
	int exitcode;
	bool closedp;
} yunoprocess;
