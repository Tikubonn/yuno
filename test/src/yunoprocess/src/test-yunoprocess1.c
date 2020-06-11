#include <yuno.h>
#include <test.h>
#include <stdbool.h>

static int globalvar;

static int entrypoint (void *localvarp){
	test(*(int*)localvarp == 0);
	test(globalvar == 0);
	*(int*)localvarp = 1;
	globalvar = 1;
	test(*(int*)localvarp == 1);
	test(globalvar == 1);
	return 0;
}

static void test1 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &localvar, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 0);
	test(globalvar == 0);
	test(close_yunoprocess(&process) == 0);
}

static void test2 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunoprocess process;
	test(make_yunoprocess(entrypoint, &localvar, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	while (true){
		int waitresult = wait_yunoprocess(YUNOFOREVER, &process);
		if (waitresult == 0){
			break;
		}
		else {
			switch (get_yunoerror()){
				case YUNOBUSY:
					nortice("wait_yunoprocess returned YUNOBUSY.");
				default:
					error("wait_yunoprocess returned YUNOERROR.");
			}
		}
	}
	int exitcode;
	test(get_yunoprocess_exit_code(&process, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 0);
	test(globalvar == 0);
	test(close_yunoprocess(&process) == 0);
}

static void test3 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunoprocess *process = new_yunoprocess(entrypoint, &localvar);
	test(process != NULL);
	test(start_yunoprocess(process) == 0);
	test(wait_yunoprocess(YUNOFOREVER, process) == 0);
	int exitcode;
	test(get_yunoprocess_exit_code(process, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 0);
	test(globalvar == 0);
	test(close_yunoprocess(process) == 0);
	test(free_yunoprocess(process) == 0);
}

static void test4 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunoprocess *process = new_yunoprocess(entrypoint, &localvar);
	test(process != NULL);
	test(start_yunoprocess(process) == 0);
	while (true){
		int waitresult = wait_yunoprocess(YUNOFOREVER, process);
		if (waitresult == 0){
			break;
		}
		else {
			switch (get_yunoerror()){
				case YUNOBUSY:
					nortice("wait_yunoprocess returned YUNOBUSY.");
				default:
					error("wait_yunoprocess returned YUNOERROR.");
			}
		}
	}
	int exitcode;
	test(get_yunoprocess_exit_code(process, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 0);
	test(globalvar == 0);
	test(close_yunoprocess(process) == 0);
	test(free_yunoprocess(process) == 0);
}

void test_yunoprocess1 (){
	test1();
	test2();
	test3();
	test4();
}
