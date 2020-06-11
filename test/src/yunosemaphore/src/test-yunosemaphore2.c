#include <yuno.h>
#include <test.h>
#include <stddef.h>

#define SLEEP_TIME 3

typedef struct process_argument {
	int *sharedint;
	yunosemaphore *semaphore;
} process_argument;

static int entrypoint (void *parameter){
	process_argument *pargument = parameter;
	test(wait_yunosemaphore(YUNOFOREVER, pargument->semaphore) == 0);
	test(yunosleep(SLEEP_TIME, 0) == 0);
	*pargument->sharedint += 1;
	test(release_yunosemaphore(pargument->semaphore) == 0);
	return 0;
}

#define PROCESS_COUNT 3

static void test1 (){
	yunosemaphore semaphore;
	test(make_yunosemaphore(1, &semaphore) == 0);
	int *sharedint = allocate_yunoshared_memory(sizeof(int));
	test(sharedint != NULL);
	*sharedint = 0;
	process_argument pargument;
	pargument.sharedint = sharedint;
	pargument.semaphore = &semaphore;
	yunoprocess processes[PROCESS_COUNT];
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(make_yunoprocess(entrypoint, &pargument, &(processes[index])) == 0);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(start_yunoprocess(&(processes[index])) == 0);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(wait_yunoprocess(YUNOFOREVER, &(processes[index])) == 0);
		test(close_yunoprocess(&(processes[index])) == 0);
	}
	test(*sharedint == PROCESS_COUNT);
	test(free_yunoshared_memory(sharedint, sizeof(int)) == 0);
	test(close_yunosemaphore(&semaphore) == 0);
}

static void test2 (){
	yunosemaphore *semaphore = new_yunosemaphore(1);
	test(semaphore != NULL);
	int *sharedint = allocate_yunoshared_memory(sizeof(int));
	test(sharedint != NULL);
	*sharedint = 0;
	process_argument pargument;
	pargument.sharedint = sharedint;
	pargument.semaphore = semaphore;
	yunoprocess processes[PROCESS_COUNT];
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(make_yunoprocess(entrypoint, &pargument, &(processes[index])) == 0);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(start_yunoprocess(&(processes[index])) == 0);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(wait_yunoprocess(YUNOFOREVER, &(processes[index])) == 0);
		test(close_yunoprocess(&(processes[index])) == 0);
	}
	test(*sharedint == PROCESS_COUNT);
	test(free_yunoshared_memory(sharedint, sizeof(int)) == 0);
	test(close_yunosemaphore(semaphore) == 0);
	test(free_yunosemaphore(semaphore) == 0);
}

void test_yunosemaphore2 (){
	test1();
	test2();
}
