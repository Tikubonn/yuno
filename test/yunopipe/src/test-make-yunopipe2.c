#include "test.h"
#include <yuno.h>

typedef struct somepipes {
	yunofile *inread;
	yunofile *inwrite;
	yunofile *outread;
	yunofile *outwrite;
} somepipes;

static int __yunocall example (void *parameter){
	somepipes *pip = parameter;
	test(close_yunofile(pip->inwrite) == YUNOFILE_SUCCESS);
	test(close_yunofile(pip->outread) == YUNOFILE_SUCCESS);
	while (1){
		char buffer[1024];
		yunosize readsize;
		test(read_yunofile(buffer, sizeof(buffer), pip->inread, &readsize) == YUNOFILE_SUCCESS);
		if (0 < readsize){
			for (yunosize woffset = 0; woffset < readsize;){
				yunosize wrotesize;
				test(write_yunofile(buffer + woffset, sizeof(buffer) - woffset, pip->outwrite, &wrotesize) == YUNOFILE_SUCCESS);
				woffset += wrotesize;
			}
		}
		else {
			break;
		}
	}
	test(close_yunofile(pip->inread) == YUNOFILE_SUCCESS);
	test(close_yunofile(pip->outwrite) == YUNOFILE_SUCCESS);
	return 0;
}

#define TEST_MESSAGE "this is a test message!"

void test_make_yunopipe2 (){
	yunofile *inread, *inwrite;
	test(make_yunopipe(0, 0, &inread, &inwrite) == YUNOPIPE_SUCCESS);
	yunofile *outread, *outwrite;
	test(make_yunopipe(0, 0, &outread, &outwrite) == YUNOPIPE_SUCCESS);
	somepipes pip;
	pip.inread = inread;
	pip.inwrite = inwrite;
	pip.outread = outread;
	pip.outwrite = outwrite;
	yunoprocess *process = make_yunoprocess(example, &pip);
	test(process != NULL);
	test(close_yunofile(pip.inread) == YUNOFILE_SUCCESS);
	test(close_yunofile(pip.outwrite) == YUNOFILE_SUCCESS);
	test(start_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	for (yunosize woffset = 0; woffset < sizeof(TEST_MESSAGE);){
		yunosize wrotesize;
		test(write_yunofile(TEST_MESSAGE + woffset, sizeof(TEST_MESSAGE) - woffset, pip.inwrite, &wrotesize) == YUNOFILE_SUCCESS);
		woffset += wrotesize;
	}
	test(close_yunofile(pip.inwrite) == YUNOFILE_SUCCESS);
	{
		char buffer[1024];
		for (yunosize roffset = 0; roffset < sizeof(buffer);){
			yunosize readsize;
			test(read_yunofile(buffer, sizeof(buffer), pip.outread, &readsize) == YUNOFILE_SUCCESS);
			if (readsize == 0){
				break;
			}
			roffset += readsize;
		}
		test_equal_string(TEST_MESSAGE, buffer);
	}
	test(close_yunofile(pip.outread) == YUNOPROCESS_SUCCESS);
	test(wait_yunoprocess(YUNOPROCESS_FOREVER, process) == YUNOPROCESS_SUCCESS);
	int exitcode;
	test(get_yunoprocess_exit_code(process, &exitcode) == YUNOPROCESS_SUCCESS);
	test(exitcode == 0);
	test(close_yunoprocess(process) == YUNOPROCESS_SUCCESS);
}
