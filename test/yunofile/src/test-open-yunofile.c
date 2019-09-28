#include <test.h>
#include <yuno.h>

#define TEST_MESSAGE "this is a test message."
#define LENGTH(string) (sizeof(string) -1)

void test_open_yunofile (){
	yunofile *file = open_yunofile("test.txt", YUNOFILE_READABLE | YUNOFILE_WRITABLE, 1024);
	test(file != NULL);
	test(yunofile_readablep(file) == true);
	test(yunofile_writablep(file) == true);
	// write
	{
		for (yunosize offset = 0; offset < LENGTH(TEST_MESSAGE);){
			yunosize wrotesize;
			test(write_yunofile(TEST_MESSAGE + offset, LENGTH(TEST_MESSAGE) - offset, file, &wrotesize) == YUNOFILE_SUCCESS);
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
			test(read_yunofile(buffer + offset, sizeof(buffer) - offset, file, &readsize) == YUNOFILE_SUCCESS);
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
