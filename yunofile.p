
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
