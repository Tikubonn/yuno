#include <yuno.private>
#include <stdbool.h>
#include <windows.h>

yunofile_status __stdcall open_yunofile_manually (const char *filename, int mode, void *bufferseq, yunosize buffersize, yunofile *file){
	DWORD access;
	DWORD share;
	DWORD creation;
	if (parse_yunofile_mode(mode, &access, &share, &creation) != 0){
		return YUNOFILE_ERROR;
	}
	HANDLE handle = CreateFile(filename, access, share, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle == INVALID_HANDLE_VALUE){
		switch (GetLastError()){
			case ERROR_FILE_NOT_FOUND:
				return YUNOFILE_DOES_NOT_EXIST;
			case ERROR_PATH_NOT_FOUND:
				return YUNOFILE_DOES_NOT_EXIST;
			default:
				return YUNOFILE_ERROR;
		}
	}
	if (mode & YUNOFILE_APPENDABLE){
		LARGE_INTEGER zero;
		zero.QuadPart = 0;
		if (SetFilePointerEx(handle, zero, NULL, FILE_END) == 0){
			return YUNOFILE_ERROR;
		}
	}
	init_yunofile(mode, handle, bufferseq, buffersize, file);
	return YUNOFILE_SUCCESS;
}
