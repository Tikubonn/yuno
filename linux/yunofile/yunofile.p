#include <stdbool.h>

typedef enum yunofile_async_status {
	YUNOFILE_FREE,
	YUNOFILE_READING,
	YUNOFILE_WRITING,
	YUNOFILE_READ_COMPLETED,
	YUNOFILE_WRITE_COMPLETED,
} yunofile_async_status;

typedef struct yunofile {
	int filefd;
	int mode;
	bool asyncp;
	yunofile_async_status asyncstatus;
	yunosize asynccompletedsize;
	yunobuffer asyncbuffer;
	bool closedp;
} yunofile;
