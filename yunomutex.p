
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
