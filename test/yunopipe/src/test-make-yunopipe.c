#include "test.h"
#include <yuno.h>

#define TEST_MESSAGE "this is a test message!"

void test_make_yunopipe (){
	yunofile *input, *output;
	test(make_yunopipe(&input, &output) == YUNOPIPE_SUCCESS);
	for (yunosize woffset = 0; woffset < sizeof(TEST_MESSAGE);){
		yunosize wrotesize;
		test(write_yunofile(TEST_MESSAGE + woffset, sizeof(TEST_MESSAGE) - woffset, output, &wrotesize) == YUNOFILE_SUCCESS);
		woffset += wrotesize;
	}
	test(close_yunofile(output) == YUNOFILE_SUCCESS);
	{
		char buffer[1024];
		for (yunosize roffset = 0; roffset < sizeof(buffer);){
			yunosize readsize;
			test(read_yunofile(buffer + roffset, sizeof(buffer) - roffset, input, &readsize) == YUNOFILE_SUCCESS);
			if (readsize == 0){
				break;
			}
			roffset += readsize;
		}
		test_equal_string(TEST_MESSAGE, buffer);
	}
	test(close_yunofile(input) == YUNOFILE_SUCCESS);
  test(free_yunofile(input) == YUNOFILE_SUCCESS);
  test(free_yunofile(output) == YUNOFILE_SUCCESS);
}
