#include <test.h>
#include <yuno.h>

static int __yunocall example (void *parameter){
	yunomutex *mutex = (yunomutex*)parameter;
	test(wait_yunomutex(YUNOMUTEX_FOREVER, mutex) == YUNOPROCESS_SUCCESS);
	test(yunosleep(1) == YUNOSLEEP_SUCCESS);
	test(release_yunomutex(mutex) == YUNOPROCESS_SUCCESS);
	return 0;
}

#define PROCESS_COUNT 3

void test_make_named_yunomutex2 (){
	yunomutex *mutexes[PROCESS_COUNT];
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		mutexes[index] = make_named_yunomutex("mutex-for-make-named-yunomutex");
		test(mutexes[index] != NULL);
	}
	yunoprocess processes[PROCESS_COUNT];
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(make_yunoprocess_manually(example, mutexes[index], &(processes[index])) == YUNOMUTEX_SUCCESS);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(start_yunoprocess(&(processes[index])) == YUNOPROCESS_SUCCESS);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(wait_yunoprocess(YUNOPROCESS_FOREVER, &(processes[index])) == YUNOPROCESS_SUCCESS);
		int exitcode;
		test(get_yunoprocess_exit_code(&(processes[index]), &exitcode) == YUNOPROCESS_SUCCESS);
		test(exitcode == 0);
		test(close_yunoprocess(&(processes[index])) == YUNOPROCESS_SUCCESS);
	}
	for (size_t index = 0; index < PROCESS_COUNT; index++){
		test(close_yunomutex(mutexes[index]) == YUNOMUTEX_SUCCESS);
		test(free_yunomutex(mutexes[index]) == YUNOMUTEX_SUCCESS);
	}
}
