
/*
	seek_yunobuffer 関数で使用される基準点の定数です
*/

typedef enum yunobuffer_whence {
	YUNOBUFFER_BEGIN,
	YUNOBUFFER_CURRENT,
	YUNOBUFFER_END,
} yunobuffer_whence;

/*
	ファイルライクな操作で指定された領域を読み書きするデータ型です
	この型は非同期IO時の一時的なバッファとして使用されます
*/

typedef struct yunobuffer {
	void *sequence;
	yunosize seek;
	yunosize seekend;
	yunosize size;
} yunobuffer;
