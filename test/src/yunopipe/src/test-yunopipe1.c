#include <yuno.h>
#include <test.h>
#include <stdbool.h>

#define TEST_DATA "abcdef"

static void test_write (yunofile *inputfile, yunofile *outputfile){
	(void)inputfile; // ignore unused variable!
	for (yunosize offset = 0; offset < sizeof(TEST_DATA) -1;){
		yunosize wrotesize;
		test(write_yunofile(TEST_DATA + offset, sizeof(TEST_DATA) - (offset + 1), outputfile, &wrotesize) == 0);
		test(0 < wrotesize);
		offset += wrotesize;
	}
}

static void test_read (yunofile *inputfile, yunofile *outputfile){
	(void)outputfile; // ignore unused variable!
	char buffer[1024];
	for (yunosize offset = 0; true;){
		yunosize readsize;
		test(read_yunofile(buffer + offset, sizeof(buffer) - (offset + 1), inputfile, &readsize) == 0);
		if (readsize == 0){
			break;
		}
		else {
			offset += readsize;
		}
	}
	for (yunosize index = 0; index < sizeof(TEST_DATA) -1; index++){
		test(buffer[index] == TEST_DATA[index]);
	}
}

#define BUFFER_SIZE 4096

static void test1 (){
	yunofile inputfile;
	yunofile outputfile;
	test(make_yunopipe(0, NULL, 0, NULL, 0, &inputfile, &outputfile) == 0);
	test_write(&inputfile, &outputfile);
	test(close_yunofile(&outputfile) == 0);
	test_read(&inputfile, &outputfile);
	test(close_yunofile(&inputfile) == 0);
}

static void test2 (){
	char inputfilebuffer[BUFFER_SIZE];
	char outputfilebuffer[BUFFER_SIZE];
	yunofile inputfile;
	yunofile outputfile;
	test(make_yunopipe(YUNOFILE_ASYNC, inputfilebuffer, sizeof(inputfilebuffer), outputfilebuffer, sizeof(outputfilebuffer), &inputfile, &outputfile) == 0);
	test_write(&inputfile, &outputfile);
	test(close_yunofile(&outputfile) == 0);
	test_read(&inputfile, &outputfile);
	test(close_yunofile(&inputfile) == 0);
}

static void test3 (){
	yunofile *inputfile;
	yunofile *outputfile;
	test(new_yunopipe(0, 0, 0, &inputfile, &outputfile) == 0);
	test_write(inputfile, outputfile);
	test(close_yunofile(outputfile) == 0);
	test_read(inputfile, outputfile);
	test(close_yunofile(inputfile) == 0);
	test(free_yunofile(inputfile) == 0);
	test(free_yunofile(outputfile) == 0);
}

static void test4 (){
	yunofile *inputfile;
	yunofile *outputfile;
	test(new_yunopipe(YUNOFILE_ASYNC, BUFFER_SIZE, BUFFER_SIZE, &inputfile, &outputfile) == 0);
	test_write(inputfile, outputfile);
	test(close_yunofile(outputfile) == 0);
	test_read(inputfile, outputfile);
	test(close_yunofile(inputfile) == 0);
	test(free_yunofile(inputfile) == 0);
	test(free_yunofile(outputfile) == 0);
}

void test_yunopipe1 (){
	test1();
	test2();
	test3();
	test4();
}
