
#ifdef __linux__
#undef __yunocall 
#define __yunocall
#endif

#ifdef _WIN32
#undef __yunocall 
#define __yunocall __stdcall
#endif

#ifdef _WIN64
#undef __yunocall 
#define __yunocall __stdcall
#endif

//typedef yunosize;
//typedef yunossize;

typedef int __yunocall (*yunoprocess_entry_point)(void*);

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

typedef int __yunocall (*yunothread_entry_point)(void*);

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

typedef enum yunoshared_memory_status {
	YUNOSHARED_MEMORY_SUCCESS,
	YUNOSHARED_MEMORY_ERROR
} yunoshared_memory_status;
#include <stdint.h>

typedef uint64_t yunosize;
typedef int64_t yunossize;
#include <stdint.h>
#include <stddef.h>

#define YUNOBYTE_BIT_COUNT 8

typedef uint8_t yunobyte; // must be over 8bits.

typedef struct yunobitarray {
	yunobyte *sequence;
	size_t size;
} yunobitarray;
#include <stdint.h>
#include <stddef.h>

#define YUNOALLOCATOR_ALIGNMENT sizeof(intmax_t)

typedef enum yunoallocator_status {
	YUNOALLOCATOR_SUCCESS,
	YUNOALLOCATOR_ERROR,
	YUNOALLOCATOR_NOT_ENOUGH_MEMORY
} yunoallocator_status;

typedef struct yunoallocator {
	yunobitarray bitmap;
	void *sequence;
	size_t size;
} yunoallocator;

/*
	offset を base の整数倍に調節するマクロです。
	yunoallocator の多くの関数で使用するのでマクロ化しています。
*/

#define ALIGN_FOR_YUNOALLOCATOR(offset, base)\
((offset) % (base) == 0 ? (offset) : ((offset) + (base) - (offset) % (base)))
#include <windows.h>
#include <stddef.h>

typedef struct yunoshared_memory {
	HANDLE handle;
	void *address;
	size_t size;
	size_t seqsize;
	size_t mapsize;
	yunoallocator allocator;
	struct yunoshared_memory *next;
} yunoshared_memory;
#include <stdio.h>

yunoshared_memory *global_yunoshared_memory;

void *yunoshared_memory_initialized1;
void *yunoshared_memory_initialized2;
void *yunoshared_memory_initialized3;

/*
	allocate_yunoshared_memory/free_yunoshared_memory の内部で利用される初期化用のマクロです。
	このマクロはアプリケーション内で最初に実行された時のみ global_yunoshared_memory の値を NULL で初期化します。
	その後に第一引数に渡された formula を評価しその結果を返します。
	雑な仕組みなので一定の確率で失敗するかもしれません。
*/

#define after_init_yunoshared_memory(formula)\
(((yunoshared_memory_initialized1!=(void*)&yunoshared_memory_initialized3)||\
(yunoshared_memory_initialized2!=(void*)&yunoshared_memory_initialized3)?\
(yunoshared_memory_initialized3=(void*)&yunoshared_memory_initialized3),\
(yunoshared_memory_initialized2=(void*)&yunoshared_memory_initialized3),\
(yunoshared_memory_initialized1=(void*)&yunoshared_memory_initialized3),\
(global_yunoshared_memory=NULL):0),(formula))

extern void __yunocall *__allocate_yunoshared_memory (size_t, yunoshared_memory**);

#define allocate_yunoshared_memory(size)\
after_init_yunoshared_memory(\
__allocate_yunoshared_memory(size, &global_yunoshared_memory))

extern yunoshared_memory_status __yunocall __free_yunoshared_memory (void*, size_t, yunoshared_memory**);

#define free_yunoshared_memory(address, size)\
after_init_yunoshared_memory(\
__free_yunoshared_memory(address, size, &global_yunoshared_memory))

extern int remap_yunoshared_memory (yunoshared_memory**);
#include <stdbool.h>

extern bool yunoshared_memory_managed_addressp (void*, yunoshared_memory**);
#include <windows.h>

typedef struct yunoprocess {
	yunoprocess_entry_point entrypoint;
	void *parameter;
	//yunoshared_memory **sharedmemoryp;
	struct  yunoshared_memory **sharedmemoryp;
	HANDLE process;
	HANDLE thread;
	HANDLE remotethread;
} yunoprocess;

extern yunoprocess_status __yunocall __make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*, yunoshared_memory**);

#define make_yunoprocess_manually(entrypoint, parameter, process)\
__make_yunoprocess_manually(entrypoint, parameter, process, &global_yunoshared_memory)

extern yunoprocess __yunocall *__make_yunoprocess (yunoprocess_entry_point, void*, yunoshared_memory**);

#define make_yunoprocess(entrypoint, parameter)\
__make_yunoprocess(entrypoint, parameter, &global_yunoshared_memory)
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


//extern yunoprocess_status __yunocall make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*);
//extern yunoprocess __yunocall *make_yunoprocess (yunoprocess_entry_point, void*);
extern yunoprocess_status __yunocall start_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall wait_yunoprocess (yunoprocess_wait_mode, yunoprocess*);
extern yunoprocess_status __yunocall close_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess*, int*);
extern yunoprocess_status __yunocall free_yunoprocess (yunoprocess*);

extern yunothread_status __yunocall make_yunothread_manually (yunothread_entry_point, void*, yunothread*);
extern yunothread __yunocall *make_yunothread (yunothread_entry_point, void*);
extern yunothread_status __yunocall start_yunothread (yunothread*);
extern yunothread_status __yunocall wait_yunothread (yunothread_wait_mode, yunothread*);
extern yunothread_status __yunocall close_yunothread (yunothread*);
extern yunothread_status __yunocall get_yunothread_exit_code (yunothread*, int*);
extern yunothread_status __yunocall free_yunothread (yunothread*);

extern yunofile_status __yunocall open_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile_status __yunocall open_async_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile __yunocall *open_yunofile (const char*, int, yunosize);
extern yunofile __yunocall *open_async_yunofile (const char*, int, yunosize);
extern bool __yunocall yunofile_readablep (yunofile*);
extern bool __yunocall yunofile_writablep (yunofile*);
extern yunofile_status __yunocall write_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __yunocall request_write_yunofile (void*, yunosize, yunofile*);
extern yunofile_status __yunocall wait_write_yunofile (yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __yunocall read_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __yunocall request_read_yunofile (yunosize, yunofile*);
extern yunofile_status __yunocall wait_read_yunofile (void*, yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __yunocall seek_yunofile (yunossize, yunofile_where, yunofile*, yunosize*);
extern yunofile_status __yunocall tell_yunofile (yunofile*, yunosize*);
extern yunofile_status __yunocall close_yunofile (yunofile*);
extern yunofile_status __yunocall free_yunofile (yunofile*);
extern yunofile_status __yunocall get_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile __yunocall *get_yunostandard_input (yunosize);
extern yunofile __yunocall *get_yunostandard_output (yunosize);
extern yunofile __yunocall *get_yunostandard_error (yunosize);
extern yunofile __yunocall *get_async_yunostandard_input (yunosize);
extern yunofile __yunocall *get_async_yunostandard_output (yunosize);
extern yunofile __yunocall *get_async_yunostandard_error (yunosize);

extern yunomutex_status __yunocall make_yunomutex_manually (yunomutex*);
extern yunomutex __yunocall *make_yunomutex ();
extern yunomutex_status __yunocall wait_yunomutex (yunomutex_wait_mode, yunomutex*);
extern yunomutex_status __yunocall release_yunomutex (yunomutex*);
extern yunomutex_status __yunocall close_yunomutex (yunomutex*);
extern yunomutex_status __yunocall free_yunomutex (yunomutex*);

extern yunosemaphore_status __yunocall make_yunosemaphore_manually (int, yunosemaphore*);
extern yunosemaphore __yunocall *make_yunosemaphore (int);
extern yunosemaphore_status __yunocall wait_yunosemaphore (yunosemaphore_wait_mode, yunosemaphore*);
extern yunosemaphore_status __yunocall release_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall close_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall free_yunosemaphore (yunosemaphore*);

extern yunosleep_status __yunocall yunosleep (int);

extern yunopipe_status __yunocall make_yunopipe_manually (yunofile*, yunofile*);
extern yunopipe_status __yunocall make_yunopipe (yunofile**, yunofile**);

//extern void __yunocall *allocate_yunoshared_memory (size_t);
//extern yunoshared_memory_status __yunocall free_yunoshared_memory (void*, size_t);
