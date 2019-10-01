#include <yuno.private>
#include <windows.h>

yunopipe_status __yunocall make_yunopipe_manually (yunofile *inputfilep, yunofile *outputfilep){
	SECURITY_ATTRIBUTES secattr;
	secattr.nLength = sizeof(secattr);
	secattr.lpSecurityDescriptor = NULL;
	secattr.bInheritHandle = TRUE;
	HANDLE input;
	HANDLE output;
	if (CreatePipe(&input, &output, &secattr, 0) == 0){
		return YUNOPIPE_ERROR;
	}
	init_yunofile(YUNOFILE_READABLE, input, NULL, 0, inputfilep);
	init_yunofile(YUNOFILE_WRITABLE, output, NULL, 0, outputfilep);
	return YUNOPIPE_SUCCESS;
}
