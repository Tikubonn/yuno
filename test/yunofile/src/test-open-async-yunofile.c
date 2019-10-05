#include "test.h"
#include <yuno.h>

#define TEST_MESSAGE "this is a test message."

void test_open_async_yunofile (){
	yunofile *file = open_async_yunofile("test.txt", YUNOFILE_READABLE | YUNOFILE_WRITABLE, 1024);
	test(file != NULL);
	test(yunofile_readablep(file) == true);
	test(yunofile_writablep(file) == true);
	// write
	{
		for (yunosize offset = 0; offset < sizeof(TEST_MESSAGE);){
			yunosize wrotesize;
			test(request_write_yunofile(TEST_MESSAGE + offset, sizeof(TEST_MESSAGE) - offset, file) == YUNOFILE_SUCCESS);
			test(wait_write_yunofile(YUNOFILE_FOREVER, file, &wrotesize) == YUNOFILE_SUCCESS);
			offset += wrotesize;
		}
	}
	// seek
	{
		yunosize newseek;
		test(seek_yunofile(0, YUNOFILE_BEGIN, file, &newseek) == YUNOFILE_SUCCESS);
	}
	// read
	{
		char buffer[1024] = {0};
		yunosize offset = 0;
		while (offset < sizeof(buffer)){
			yunosize readsize;
			test(request_read_yunofile(sizeof(buffer) - offset, file) == YUNOFILE_SUCCESS);
			test(wait_read_yunofile(buffer + offset, YUNOFILE_FOREVER, file, &readsize) == YUNOFILE_SUCCESS);
			if (readsize == 0){
				break;
			}
			offset += readsize;
		}
		test_equal_string(TEST_MESSAGE, buffer);
	}
	test(close_yunofile(file) == YUNOFILE_SUCCESS);
	test(free_yunofile(file) == YUNOFILE_SUCCESS);
}
