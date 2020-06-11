#include <windows.h>
#include <stdbool.h>

typedef enum yunofile_type {
	TYPE_YUNOFILE,
	TYPE_YUNOSERVER_PIPE,
	TYPE_YUNOCLIENT_PIPE,
} yunofile_type;

typedef enum yunofile_async_status {
	YUNOFILE_FREE,
	YUNOFILE_WRITING,
	YUNOFILE_READING,
	YUNOFILE_WRITE_COMPLETED,
	YUNOFILE_READ_COMPLETED,
} yunofile_async_status;

typedef struct yunofile {
	yunofile_type type;
	int mode;
	HANDLE file;
	HANDLE event;
	bool asyncp; 
	yunosize asyncseek; // used to async IO.
	yunofile_async_status asyncstatus; // used to async IO.
	yunosize asynccompletedsize; // used to async IO.
	OVERLAPPED asyncoverlapped; // used to async IO.
	yunobuffer asyncbuffer; // used to async IO.
	bool closedp;
} yunofile;
