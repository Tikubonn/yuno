#include <yuno.h>
#include <test.h>

static int entrypoint (void *parameter){
	int *newinteger = parameter;
	test(*newinteger == 1);
	*newinteger = 2;
	test(sync_yunoshared_memory(newinteger) == 0);
	return 0;
}

static void test1 (){
	int *newinteger = allocate_yunoshared_memory(sizeof(int));
	test(newinteger != NULL);
	*newinteger = 1;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, newinteger, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(close_yunoprocess(&process) == 0);
	test(*newinteger == 2);
	test(free_yunoshared_memory(newinteger, sizeof(int)) == 0);
}

void test_yunoshared_memory2 (){
	test1();
}
