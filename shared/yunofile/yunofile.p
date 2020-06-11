
/*
	open_yunofile 系関数でどのようにファイルを開くかを指示する定数群です
*/

#define YUNOFILE_READABLE (1 << 0)
#define YUNOFILE_WRITABLE (1 << 1)
#define YUNOFILE_TRUNCATE (1 << 2)
#define YUNOFILE_APPEND (1 << 3)
#define YUNOFILE_SYNC (1 << 4)
#define YUNOFILE_ASYNC (1 << 5)

/*
	seek_yunofile 関数で使用される基準点を表す定数です
*/

typedef enum yunofile_whence {
	YUNOFILE_BEGIN,
	YUNOFILE_CURRENT,
	YUNOFILE_END,
} yunofile_whence;
