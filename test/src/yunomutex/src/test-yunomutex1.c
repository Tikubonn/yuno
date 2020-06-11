#include <yuno.h>
#include <test.h>
#include <stddef.h>

static int globalvar;

#define SLEEP_TIME 3

static int entrypoint (void *parameter){
	yunomutex *mutex = parameter;
	test(wait_yunomutex(YUNOFOREVER, mutex) == 0);
	test(yunosleep(SLEEP_TIME, 0) == 0);
	globalvar += 1;
	test(release_yunomutex(mutex) == 0);
	return 0;
}

#define THREAD_COUNT 3

static void test1 (){
	globalvar = 0;
	yunomutex mutex;
	test(make_yunomutex(&mutex) == 0);
	yunothread threads[THREAD_COUNT];
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(make_yunothread(entrypoint, &mutex, &(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(start_yunothread(&(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(wait_yunothread(YUNOFOREVER, &(threads[index])) == 0);
		test(close_yunothread(&(threads[index])) == 0);
	}
	test(globalvar == THREAD_COUNT);
	test(close_yunomutex(&mutex) == 0);
}

static void test2 (){
	globalvar = 0;
	yunomutex *mutex = new_yunomutex();
	test(mutex != NULL);
	yunothread threads[THREAD_COUNT];
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(make_yunothread(entrypoint, mutex, &(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(start_yunothread(&(threads[index])) == 0);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(wait_yunothread(YUNOFOREVER, &(threads[index])) == 0);
		test(close_yunothread(&(threads[index])) == 0);
	}
	test(globalvar == THREAD_COUNT);
	test(close_yunomutex(mutex) == 0);
	test(free_yunomutex(mutex) == 0);
}

void test_yunomutex1 (){
	test1();
	test2();
}
