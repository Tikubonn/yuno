
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
