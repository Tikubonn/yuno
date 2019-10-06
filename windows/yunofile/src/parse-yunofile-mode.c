#include <yuno.private>
#include <windows.h>

/*
	モードを表す整数から CreateFile で要求される幾つかの整数を返す関数です。
	この関数は成功した場合には 0 を返し、失敗した場合には非ゼロの整数を返します。
*/

int parse_yunofile_mode (int mode, DWORD *accessp, DWORD *sharep, DWORD *creationp){
  switch (mode){
		case YUNOFILE_READABLE: 
			*accessp = GENERIC_READ;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_EXISTING;
			return 0;
		case YUNOFILE_WRITABLE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_WRITABLE | YUNOFILE_APPEND: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_TRUNCATE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE | YUNOFILE_APPEND: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
    default:
      return 1; // unknown combination!
  }
  /*
	switch (mode){
		case YUNOFILE_READABLE: 
			*accessp = GENERIC_READ;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_EXISTING;
			return 0;
		case YUNOFILE_WRITABLE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_APPENDABLE: 
			*accessp = GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_WRITABLE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = CREATE_ALWAYS;
			return 0;
		case YUNOFILE_READABLE | YUNOFILE_APPENDABLE: 
			*accessp = GENERIC_READ | GENERIC_WRITE;
			*sharep = FILE_SHARE_READ | FILE_SHARE_WRITE;
			*creationp = OPEN_ALWAYS;
			return 0;
		default:
			return 1; // unknown combination!
	}
  */
}
