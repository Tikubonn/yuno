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
