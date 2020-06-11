#include <yuno.h>
#include <test.h>
#include <stddef.h>

static int globalvar = 0;

static int entrypoint (void *parameter){
	int waitcount = (int)parameter;
	test(yunosleep(waitcount, 0) == 0);
	globalvar = waitcount;
	return 0;
}

#define THREAD_COUNT 3

static void test1 (){
	yunothread threads[THREAD_COUNT];
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(make_yunothread(entrypoint, (void*)index +1, &(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(start_yunothread(&(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(wait_yunothread(YUNOFOREVER, &(threads[index])) == 0);
		test(close_yunothread(&(threads[index])) == 0);
	}
	test(globalvar == THREAD_COUNT);
}

void test_yunosleep1 (){
	test1();
}
