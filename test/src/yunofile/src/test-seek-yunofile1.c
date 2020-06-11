#include <yuno.h>
#include <test.h>

#define TEST_DATA "abcdef"

static void test_seek (yunofile *file){
	{
		for (yunosize offset = 0; offset < sizeof(TEST_DATA) -1;){
			yunosize wrotesize;
			test(write_yunofile(TEST_DATA + offset, sizeof(TEST_DATA) - (offset + 1), file, &wrotesize) == 0);
			offset += wrotesize;
		}
	}
	{
		yunosize offset;
		test(tell_yunofile(file, &offset) == 0);
		test(offset == sizeof(TEST_DATA) -1);
	}
	{
		yunosize newoffset;
		test(seek_yunofile(3, YUNOFILE_BEGIN, file, &newoffset) == 0);
		test(newoffset == 3);
	}
	{
		yunosize newoffset;
		test(seek_yunofile(3, YUNOFILE_CURRENT, file, &newoffset) == 0);
		test(newoffset == 6);
	}
	{
		yunosize newoffset;
		test(seek_yunofile(0, YUNOFILE_END, file, &newoffset) == 0);
		test(newoffset == sizeof(TEST_DATA) -1);
	}
}

#define BUFFER_SIZE 1024

static void test1 (){
	yunofile file;
	test(open_yunofile("test.txt", YUNOFILE_WRITABLE, NULL, 0, &file) == 0);
	test(yunofile_readablep(&file) == false);
	test(yunofile_writablep(&file) == true);
	test(yunofile_closedp(&file) == false);
	test_seek(&file);
	test(close_yunofile(&file) == 0);
	test(yunofile_closedp(&file) == true);
}

static void test2 (){
	char buffer[BUFFER_SIZE];
	yunofile file;
	test(open_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_ASYNC, buffer, sizeof(buffer), &file) == 0);
	test(yunofile_readablep(&file) == false);
	test(yunofile_writablep(&file) == true);
	test(yunofile_closedp(&file) == false);
	test_seek(&file);
	test(close_yunofile(&file) == 0);
	test(yunofile_closedp(&file) == true);
}

static void test3 (){
	yunofile *file = new_yunofile("test.txt", YUNOFILE_WRITABLE, 0);
	test(file != NULL);
	test(yunofile_readablep(file) == false);
	test(yunofile_writablep(file) == true);
	test(yunofile_closedp(file) == false);
	test_seek(file);
	test(close_yunofile(file) == 0);
	test(yunofile_closedp(file) == true);
	test(free_yunofile(file) == 0);
}

static void test4 (){
	yunofile *file = new_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_ASYNC, BUFFER_SIZE);
	test(file != NULL);
	test(yunofile_readablep(file) == false);
	test(yunofile_writablep(file) == true);
	test(yunofile_closedp(file) == false);
	test_seek(file);
	test(close_yunofile(file) == 0);
	test(yunofile_closedp(file) == true);
	test(free_yunofile(file) == 0);
}

void test_seek_yunofile1 (){
	test1();
	test2();
	test3();
	test4();
}
