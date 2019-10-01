#include <test.h>
#include <yuno.h>

static int global_number;

static int __yunocall example (void *parameter){
	test(global_number == 0);
	global_number = 1;
	test(global_number == 1);
	return 0;
}

void test_make_yunoprocess2 (){
	global_number = 0; // set 0 to global variable!
	yunoprocess *process = make_yunoprocess(example, NULL);
	test(process != NULL);
	test(start_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	test(wait_yunoprocess(YUNOPROCESS_FOREVER, process) == YUNOPROCESS_SUCCESS);
	int exitcode;
	test(get_yunoprocess_exit_code(process, &exitcode) == YUNOPROCESS_SUCCESS);
	test(exitcode == 0);
	test(close_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	test(global_number == 0);
	test(free_yunoprocess(process) == YUNOPROCESS_SUCCESS);
}
