
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
#include <stdint.h>

typedef uint64_t yunosize;
typedef int64_t yunossize;
#include <windows.h>

typedef struct yunoprocess {
	yunoprocess_entry_point entrypoint;
	void *parameter;
	HANDLE process;
	HANDLE thread;
	HANDLE remotethread;
} yunoprocess;
#include <windows.h>

typedef struct yunothread {
	yunothread_entry_point entrypoint;
	void *parameter;
	HANDLE thread;
} yunothread;
#include <stddef.h>

typedef struct yunofile_buffer {
	char *sequence;
	yunosize size;
	yunosize seek;
} yunofile_buffer;
#include <windows.h>
#include <stdbool.h>

typedef enum yunofile_request_status {
	YUNOFILE_FREE,
	YUNOFILE_WRITING,
	YUNOFILE_READING,
	YUNOFILE_WRITE_COMPLETED,
	YUNOFILE_READ_COMPLETED
} yunofile_request_status;

typedef struct yunofile {
	int mode;
	HANDLE file;
	bool asyncp; //! 非同期モードで使用
	yunosize asyncseek; //! 非同期モードで使用
	yunofile_request_status requeststatus; //! 非同期モードで使用 
	yunosize completedsize; //! 非同期モードで使用
	OVERLAPPED overlapped; //! 非同期モードで使用 
	yunofile_buffer buffer; //! 非同期モードで使用
} yunofile;
#include <windows.h>

typedef struct yunomutex {
	HANDLE mutex;
} yunomutex;
#include <windows.h>

typedef struct yunosemaphore {
	HANDLE semaphore;
} yunosemaphore;


extern yunoprocess_status __stdcall make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*);
extern yunoprocess __stdcall *make_yunoprocess (yunoprocess_entry_point, void*);
extern yunoprocess_status __stdcall start_yunoprocess (yunoprocess*);
extern yunoprocess_status __stdcall wait_yunoprocess (yunoprocess_wait_mode, yunoprocess*);
extern yunoprocess_status __stdcall close_yunoprocess (yunoprocess*);
extern yunoprocess_status __stdcall get_yunoprocess_exit_code (yunoprocess*, int*);
extern yunoprocess_status __stdcall free_yunoprocess (yunoprocess*);

extern yunothread_status __stdcall make_yunothread_manually (yunothread_entry_point, void*, yunothread*);
extern yunothread __stdcall *make_yunothread (yunothread_entry_point, void*);
extern yunothread_status __stdcall start_yunothread (yunothread*);
extern yunothread_status __stdcall wait_yunothread (yunothread_wait_mode, yunothread*);
extern yunothread_status __stdcall close_yunothread (yunothread*);
extern yunothread_status __stdcall get_yunothread_exit_code (yunothread*, int*);
extern yunothread_status __stdcall free_yunothread (yunothread*);

extern yunofile_status __stdcall open_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_async_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile __stdcall *open_yunofile (const char*, int, yunosize);
extern yunofile __stdcall *open_async_yunofile (const char*, int, yunosize);
extern bool __stdcall yunofile_readablep (yunofile*);
extern bool __stdcall yunofile_writablep (yunofile*);
extern yunofile_status __stdcall write_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __stdcall request_write_yunofile (void*, yunosize, yunofile*);
extern yunofile_status __stdcall wait_write_yunofile (yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __stdcall read_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __stdcall request_read_yunofile (yunosize, yunofile*);
extern yunofile_status __stdcall wait_read_yunofile (void*, yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __stdcall seek_yunofile (yunossize, yunofile_where, yunofile*, yunosize*);
extern yunofile_status __stdcall tell_yunofile (yunofile*, yunosize*);
extern yunofile_status __stdcall close_yunofile (yunofile*);
extern yunofile_status __stdcall free_yunofile (yunofile*);
extern yunofile_status __stdcall open_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_async_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_async_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __stdcall open_async_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile __stdcall *open_yunostandard_input (yunosize);
extern yunofile __stdcall *open_yunostandard_output (yunosize);
extern yunofile __stdcall *open_yunostandard_error (yunosize);
extern yunofile __stdcall *open_async_yunostandard_input (yunosize);
extern yunofile __stdcall *open_async_yunostandard_output (yunosize);
extern yunofile __stdcall *open_async_yunostandard_error (yunosize);

extern yunomutex_status __stdcall make_yunomutex_manually (yunomutex*);
extern yunomutex_status __stdcall make_named_yunomutex_manually (const char*, yunomutex*);
extern yunomutex __stdcall *make_yunomutex ();
extern yunomutex __stdcall *make_named_yunomutex (const char*);
extern yunomutex_status __stdcall wait_yunomutex (yunomutex_wait_mode, yunomutex*);
extern yunomutex_status __stdcall release_yunomutex (yunomutex*);
extern yunomutex_status __stdcall close_yunomutex (yunomutex*);
extern yunomutex_status __stdcall free_yunomutex (yunomutex*);

extern yunosemaphore_status __stdcall make_yunosemaphore_manually (int, yunosemaphore*);
extern yunosemaphore_status __stdcall make_named_yunosemaphore_manually (const char*, int, yunosemaphore*);
extern yunosemaphore __stdcall *make_yunosemaphore (int);
extern yunosemaphore __stdcall *make_named_yunosemaphore (const char*, int);
extern yunosemaphore_status __stdcall wait_yunosemaphore (yunosemaphore_wait_mode, yunosemaphore*);
extern yunosemaphore_status __stdcall release_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __stdcall close_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __stdcall free_yunosemaphore (yunosemaphore*);

extern yunosleep_status __stdcall yunosleep (int);

extern yunopipe_status __stdcall make_yunopipe_manually (yunofile*, yunofile*);
extern yunopipe_status __stdcall make_yunopipe (yunofile**, yunofile**);
