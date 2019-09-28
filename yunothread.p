
typedef int __stdcall (*yunothread_entry_point)(void*);

//typedef yunothread;

typedef enum yunothread_status {
	YUNOTHREAD_SUCCESS,
	YUNOTHREAD_ERROR,
	YUNOTHREAD_BUSY
} yunothread_status;

typedef enum yunothread_wait_mode {
	YUNOTHREAD_FOREVER,
	YUNOTHREAD_NOWAIT
} yunothread_wait_mode;
