
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
