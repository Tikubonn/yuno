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

typedef struct fileset {
	yunofile *inputfile;
	yunofile *outputfile;
} fileset;

static int entrypoint (void *parameter){
	fileset *fset = parameter;
	test(close_yunofile(fset->outputfile) == 0);
	test_read(fset->inputfile, NULL);
	test(close_yunofile(fset->inputfile) == 0);
	return 0;
}

#define BUFFER_SIZE 4096

static void test1 (){
	yunofile inputfile;
	yunofile outputfile;
	test(make_yunopipe(0, NULL, 0, NULL, 0, &inputfile, &outputfile) == 0);
	fileset fset;
	fset.inputfile = &inputfile;
	fset.outputfile = &outputfile;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &fset, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(close_yunofile(&inputfile) == 0);
	test_write(&inputfile, &outputfile);
	test(close_yunofile(&outputfile) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(close_yunoprocess(&process) == 0);
}

static void test2 (){
	char inputfilebuffer[BUFFER_SIZE];
	char outputfilebuffer[BUFFER_SIZE];
	yunofile inputfile;
	yunofile outputfile;
	test(make_yunopipe(YUNOFILE_ASYNC, inputfilebuffer, sizeof(inputfilebuffer), outputfilebuffer, sizeof(outputfilebuffer), &inputfile, &outputfile) == 0);
	fileset fset;
	fset.inputfile = &inputfile;
	fset.outputfile = &outputfile;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &fset, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(close_yunofile(&inputfile) == 0);
	test_write(&inputfile, &outputfile);
	test(close_yunofile(&outputfile) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(close_yunoprocess(&process) == 0);
}

static void test3 (){
	yunofile *inputfile;
	yunofile *outputfile;
	test(new_yunopipe(0, 0, 0, &inputfile, &outputfile) == 0);
	fileset fset;
	fset.inputfile = inputfile;
	fset.outputfile = outputfile;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &fset, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(close_yunofile(inputfile) == 0);
	test_write(inputfile, outputfile);
	test(close_yunofile(outputfile) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(close_yunoprocess(&process) == 0);
	test(free_yunofile(inputfile) == 0);
	test(free_yunofile(outputfile) == 0);
}

static void test4 (){
	yunofile *inputfile;
	yunofile *outputfile;
	test(new_yunopipe(YUNOFILE_ASYNC, BUFFER_SIZE, BUFFER_SIZE, &inputfile, &outputfile) == 0);
	fileset fset;
	fset.inputfile = inputfile;
	fset.outputfile = outputfile;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &fset, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(close_yunofile(inputfile) == 0);
	test_write(inputfile, outputfile);
	test(close_yunofile(outputfile) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(close_yunoprocess(&process) == 0);
	test(free_yunofile(inputfile) == 0);
	test(free_yunofile(outputfile) == 0);
}

void test_yunopipe2 (){
	test1();
	test2();
	test3();
	test4();
}
