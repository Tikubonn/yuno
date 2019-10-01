#include <test.h>
#include <yuno.h>

static int __yunocall example (void *parameter){
	yunosemaphore *semaphore = parameter;
	test(wait_yunosemaphore(YUNOSEMAPHORE_FOREVER, semaphore) == YUNOSEMAPHORE_SUCCESS);
	yunosleep(1);
	test(release_yunosemaphore(semaphore) == YUNOSEMAPHORE_SUCCESS);
	return 0;
}

#define THREAD_COUNT 12

void test_make_yunosemaphore (){
	yunosemaphore *semaphore = make_yunosemaphore(3);
	test(semaphore != NULL);
	yunothread *threads[THREAD_COUNT];
	for (size_t index = 0; index < THREAD_COUNT; index++){
		threads[index] = make_yunothread(example, semaphore);
		test(threads[index] != NULL);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(start_yunothread(threads[index]) == YUNOTHREAD_SUCCESS);
	}
	for (size_t index = 0; index < THREAD_COUNT; index++){
		test(wait_yunothread(YUNOTHREAD_FOREVER, threads[index]) == YUNOTHREAD_SUCCESS);
		test(close_yunothread(threads[index]) == YUNOTHREAD_SUCCESS);
		test(free_yunothread(threads[index]) == YUNOTHREAD_SUCCESS);
	}
	test(close_yunosemaphore(semaphore) == YUNOSEMAPHORE_SUCCESS);
	test(free_yunosemaphore(semaphore) == YUNOSEMAPHORE_SUCCESS);
}
