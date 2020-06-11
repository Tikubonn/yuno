#include <yuno.h>
#include <test.h>
#include <stdbool.h>

#define TEST_DATA "abcdef"

static void test_write (yunofile *file){
	for (yunosize offset = 0; offset < sizeof(TEST_DATA) -1;){
		yunosize wrotesize;
		test(write_yunofile(TEST_DATA + offset, sizeof(TEST_DATA) - (offset + 1), file, &wrotesize) == 0);
		offset += wrotesize;
	}
	yunosize offset;
	test(tell_yunofile(file, &offset) == 0);
	test(offset == sizeof(TEST_DATA) -1);
}

static void test_append (yunofile *file){
	for (yunosize offset = 0; offset < sizeof(TEST_DATA) -1;){
		yunosize wrotesize;
		test(write_yunofile(TEST_DATA + offset, sizeof(TEST_DATA) - (offset + 1), file, &wrotesize) == 0);
		offset += wrotesize;
	}
	yunosize offset;
	test(tell_yunofile(file, &offset) == 0);
	test(offset == (sizeof(TEST_DATA) - 1) * 2);
}

static void test_read (yunofile *file){
	char readarray[1024];
	for (yunosize offset = 0; offset < (sizeof(TEST_DATA) -1) * 2;){
		yunosize readsize;
		test(read_yunofile(readarray + offset, sizeof(readarray) - offset, file, &readsize) == 0);
		if (readsize == 0){
			break;
		}
		else {
			offset += readsize;
		}
	}
	for (yunosize index = 0; index < (sizeof(TEST_DATA) -1) * 2; index++){
		test(readarray[index] == TEST_DATA[index % (sizeof(TEST_DATA) -1)]);
	}
	yunosize offset;
	test(tell_yunofile(file, &offset) == 0);
	test(offset == (sizeof(TEST_DATA) - 1) * 2);
}

#define BUFFER_SIZE 1024

static void test1 (){
	{
		yunofile fileforwrite;
		test(open_yunofile("test.txt", YUNOFILE_WRITABLE, NULL, 0, &fileforwrite) == 0);
		test(yunofile_readablep(&fileforwrite) == false);
		test(yunofile_writablep(&fileforwrite) == true);
		test(yunofile_closedp(&fileforwrite) == false);
		test_write(&fileforwrite);
		test(close_yunofile(&fileforwrite) == 0);
		test(yunofile_closedp(&fileforwrite) == true);
	}
	{
		yunofile fileforwrite;
		test(open_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_APPEND, NULL, 0, &fileforwrite) == 0);
		test(yunofile_readablep(&fileforwrite) == false);
		test(yunofile_writablep(&fileforwrite) == true);
		test(yunofile_closedp(&fileforwrite) == false);
		test_append(&fileforwrite);
		test(close_yunofile(&fileforwrite) == 0);
		test(yunofile_closedp(&fileforwrite) == true);
	}
	{
		yunofile fileforread;
		test(open_yunofile("test.txt", YUNOFILE_READABLE, NULL, 0, &fileforread) == 0);
		test(yunofile_readablep(&fileforread) == true);
		test(yunofile_writablep(&fileforread) == false);
		test(yunofile_closedp(&fileforread) == false);
		test_read(&fileforread);
		test(close_yunofile(&fileforread) == 0);
		test(yunofile_closedp(&fileforread) == true);
	}
}

static void test2 (){
	{
		char buffer[BUFFER_SIZE];
		yunofile fileforwrite;
		test(open_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_ASYNC, buffer, sizeof(buffer), &fileforwrite) == 0);
		test(yunofile_readablep(&fileforwrite) == false);
		test(yunofile_writablep(&fileforwrite) == true);
		test(yunofile_closedp(&fileforwrite) == false);
		test_write(&fileforwrite);
		test(close_yunofile(&fileforwrite) == 0);
		test(yunofile_closedp(&fileforwrite) == true);
	}
	{
		char buffer[BUFFER_SIZE];
		yunofile fileforwrite;
		test(open_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_APPEND | YUNOFILE_ASYNC, buffer, sizeof(buffer), &fileforwrite) == 0);
		test(yunofile_readablep(&fileforwrite) == false);
		test(yunofile_writablep(&fileforwrite) == true);
		test(yunofile_closedp(&fileforwrite) == false);
		test_append(&fileforwrite);
		test(close_yunofile(&fileforwrite) == 0);
		test(yunofile_closedp(&fileforwrite) == true);
	}
	{
		char buffer[BUFFER_SIZE];
		yunofile fileforread;
		test(open_yunofile("test.txt", YUNOFILE_READABLE | YUNOFILE_ASYNC, buffer, sizeof(buffer), &fileforread) == 0);
		test(yunofile_readablep(&fileforread) == true);
		test(yunofile_writablep(&fileforread) == false);
		test(yunofile_closedp(&fileforread) == false);
		test_read(&fileforread);
		test(close_yunofile(&fileforread) == 0);
		test(yunofile_closedp(&fileforread) == true);
	}
}

static void test3 (){
	{
		yunofile *fileforwrite = new_yunofile("test.txt", YUNOFILE_WRITABLE, 0);
		test(fileforwrite != NULL);
		test(yunofile_readablep(fileforwrite) == false);
		test(yunofile_writablep(fileforwrite) == true);
		test(yunofile_closedp(fileforwrite) == false);
		test_write(fileforwrite);
		test(close_yunofile(fileforwrite) == 0);
		test(yunofile_closedp(fileforwrite) == true);
		test(free_yunofile(fileforwrite) == 0);
	}
	{
		yunofile *fileforwrite = new_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_APPEND, 0);
		test(fileforwrite != NULL);
		test(yunofile_readablep(fileforwrite) == false);
		test(yunofile_writablep(fileforwrite) == true);
		test(yunofile_closedp(fileforwrite) == false);
		test_append(fileforwrite);
		test(close_yunofile(fileforwrite) == 0);
		test(yunofile_closedp(fileforwrite) == true);
		test(free_yunofile(fileforwrite) == 0);
	}
	{
		yunofile *fileforread = new_yunofile("test.txt", YUNOFILE_READABLE, 0);
		test(fileforread != NULL);
		test(yunofile_readablep(fileforread) == true);
		test(yunofile_writablep(fileforread) == false);
		test(yunofile_closedp(fileforread) == false);
		test_read(fileforread);
		test(close_yunofile(fileforread) == 0);
		test(yunofile_closedp(fileforread) == true);
		test(free_yunofile(fileforread) == 0);
	}
}

static void test4 (){
	{
		yunofile *fileforwrite = new_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_ASYNC, BUFFER_SIZE);
		test(fileforwrite != NULL);
		test(yunofile_readablep(fileforwrite) == false);
		test(yunofile_writablep(fileforwrite) == true);
		test(yunofile_closedp(fileforwrite) == false);
		test_write(fileforwrite);
		test(close_yunofile(fileforwrite) == 0);
		test(yunofile_closedp(fileforwrite) == true);
		test(free_yunofile(fileforwrite) == 0);
	}
	{
		yunofile *fileforwrite = new_yunofile("test.txt", YUNOFILE_WRITABLE | YUNOFILE_APPEND | YUNOFILE_ASYNC, BUFFER_SIZE);
		test(fileforwrite != NULL);
		test(yunofile_readablep(fileforwrite) == false);
		test(yunofile_writablep(fileforwrite) == true);
		test(yunofile_closedp(fileforwrite) == false);
		test_append(fileforwrite);
		test(close_yunofile(fileforwrite) == 0);
		test(yunofile_closedp(fileforwrite) == true);
		test(free_yunofile(fileforwrite) == 0);
	}
	{
		yunofile *fileforread = new_yunofile("test.txt", YUNOFILE_READABLE | YUNOFILE_ASYNC, BUFFER_SIZE);
		test(fileforread != NULL);
		test(yunofile_readablep(fileforread) == true);
		test(yunofile_writablep(fileforread) == false);
		test(yunofile_closedp(fileforread) == false);
		test_read(fileforread);
		test(close_yunofile(fileforread) == 0);
		test(yunofile_closedp(fileforread) == true);
		test(free_yunofile(fileforread) == 0);
	}
}

void test_yunofile3 (){
	test1();
	test2();
	test3();
	test4();
}
