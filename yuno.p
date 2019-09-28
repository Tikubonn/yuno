
//typedef yunosize;
//typedef yunossize;

typedef int __stdcall (*yunoprocess_entry_point)(void*);

//typedef struct yunoprocess;

typedef enum yunoprocess_status {
	YUNOPROCESS_SUCCESS,
	YUNOPROCESS_ERROR,
	YUNOPROCESS_BUSY
} yunoprocess_status;

typedef enum yunoprocess_wait_mode {
	YUNOPROCESS_FOREVER,
	YUNOPROCESS_NOWAIT
} yunoprocess_wait_mode;

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

#define YUNOFILE_READABLE (1 << 0)
#define YUNOFILE_WRITABLE (1 << 1)
#define YUNOFILE_APPENDABLE (1 << 2)

//typedef yunofile;

typedef enum yunofile_status {
	YUNOFILE_SUCCESS,
	YUNOFILE_ERROR,
	YUNOFILE_BUSY,
	YUNOFILE_DOES_NOT_EXIST
} yunofile_status;

typedef enum yunofile_where {
	YUNOFILE_BEGIN,
	YUNOFILE_CURRENT,
	YUNOFILE_END
} yunofile_where;

typedef enum yunofile_wait_mode {
	YUNOFILE_FOREVER,
	YUNOFILE_NOWAIT
} yunofile_wait_mode;

//typedef yunomutex;

typedef enum yunomutex_status {
	YUNOMUTEX_SUCCESS,
	YUNOMUTEX_ERROR,
	YUNOMUTEX_BUSY
} yunomutex_status;

typedef enum yunomutex_wait_mode {
	YUNOMUTEX_FOREVER,
	YUNOMUTEX_NOWAIT
} yunomutex_wait_mode;

//typedef yunosemaphore;

typedef enum yunosemaphore_status {
	YUNOSEMAPHORE_SUCCESS,
	YUNOSEMAPHORE_ERROR,
	YUNOSEMAPHORE_BUSY
} yunosemaphore_status;

typedef enum yunosemaphore_wait_mode {
	YUNOSEMAPHORE_FOREVER,
	YUNOSEMAPHORE_NOWAIT
} yunosemaphore_wait_mode;

//typedef int yunotime;

typedef enum yunosleep_status {
	YUNOSLEEP_SUCCESS,
	YUNOSLEEP_ERROR
} yunosleep_status;

typedef enum yunopipe_status {
	YUNOPIPE_SUCCESS,
	YUNOPIPE_ERROR
} yunopipe_status;
