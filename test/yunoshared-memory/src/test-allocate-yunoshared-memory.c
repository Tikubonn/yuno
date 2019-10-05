#include "test.h"
#include <yuno.h>

static int __yunocall example (void *parameter){
	int *sharedint = parameter;
	test(*sharedint == 3);
	*sharedint = 1;
	test(*sharedint == 1);
	return 0;
}

void test_allocate_yunoshared_memory (){
	int *sharedint = allocate_yunoshared_memory(sizeof(int));
	test(sharedint != NULL);
	*sharedint = 3;
	test(*sharedint == 3);
	yunoprocess *process = make_yunoprocess(example, sharedint);
	test(process != NULL);
	test(start_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	test(wait_yunoprocess(YUNOPROCESS_FOREVER, process) == YUNOPROCESS_SUCCESS);
	int exitcode;
	test(get_yunoprocess_exit_code(process, &exitcode) == YUNOPROCESS_SUCCESS);
	test(exitcode == 0);
	test(close_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	test(free_yunoprocess(process) == YUNOPROCESS_SUCCESS);
	test(*sharedint == 1);
	test(free_yunoshared_memory(sharedint, sizeof(int)) == YUNOSHARED_MEMORY_SUCCESS);
}
