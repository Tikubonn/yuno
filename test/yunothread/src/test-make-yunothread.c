#include <test.h>
#include <yuno.h>

static int global_number;

static int __yunocall example (void *parameter){
	test(global_number == 0);
	global_number = 1;
	test(global_number == 1);
	return 0;
}

void test_make_yunothread (){
	global_number = 0; // set 0 to global variable!
	yunothread thread;
	test(make_yunothread_manually(example, NULL, &thread) == YUNOTHREAD_SUCCESS);
	test(start_yunothread(&thread) == YUNOTHREAD_SUCCESS);
	test(wait_yunothread(YUNOTHREAD_FOREVER, &thread) == YUNOTHREAD_SUCCESS);
	int exitcode;
	test(get_yunothread_exit_code(&thread, &exitcode) == YUNOTHREAD_SUCCESS);
	test(exitcode == 0);
	test(close_yunothread(&thread) == YUNOTHREAD_SUCCESS);
	test(global_number == 1);
}
