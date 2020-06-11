#include <yuno.h>
#include <test.h>
#include <stdbool.h>

static int globalvar;

static int entrypoint (void *localvarp){
	test(*(int*)localvarp == 0);
	test(globalvar == 0);
	*(int*)localvarp = 1;
	globalvar = 1;
	return 0;
}

static void test1 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunothread thread;
	test(make_yunothread(entrypoint, &localvar, &thread) == 0);
	test(start_yunothread(&thread) == 0);
	test(wait_yunothread(YUNOFOREVER, &thread) == 0);
	int exitcode;
	test(get_yunothread_exit_code(&thread, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 1);
	test(globalvar == 1);
	test(close_yunothread(&thread) == 0);
}

static void test2 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunothread thread;
	test(make_yunothread(entrypoint, &localvar, &thread) == 0);
	test(start_yunothread(&thread) == 0);
	while (true){
		int waitresult = wait_yunothread(YUNOFOREVER, &thread);
		if (waitresult == 0){
			break;
		}
		else {
			switch (get_yunoerror()){
				case YUNOBUSY:
					nortice("wait_yunothread returned YUNOBUSY.");
				default:
					error("wait_yunothread returned YUNOERROR.");
			}
		}
	}
	int exitcode;
	test(get_yunothread_exit_code(&thread, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 1);
	test(globalvar == 1);
	test(close_yunothread(&thread) == 0);
}

static void test3 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunothread *thread = new_yunothread(entrypoint, &localvar);
	test(thread != NULL);
	test(start_yunothread(thread) == 0);
	test(wait_yunothread(YUNOFOREVER, thread) == 0);
	int exitcode;
	test(get_yunothread_exit_code(thread, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 1);
	test(globalvar == 1);
	test(close_yunothread(thread) == 0);
	test(free_yunothread(thread) == 0);
}

static void test4 (){
	int localvar;
	globalvar = 0;
	localvar = 0;
	yunothread *thread = new_yunothread(entrypoint, &localvar);
	test(thread != NULL);
	test(start_yunothread(thread) == 0);
	while (true){
		int waitresult = wait_yunothread(YUNOFOREVER, thread);
		if (waitresult == 0){
			break;
		}
		else {
			switch (get_yunoerror()){
				case YUNOBUSY:
					nortice("wait_yunothread returned YUNOBUSY.");
				default:
					error("wait_yunothread returned YUNOERROR.");
			}
		}
	}
	int exitcode;
	test(get_yunothread_exit_code(thread, &exitcode) == 0);
	test(exitcode == 0);
	test(localvar == 1);
	test(globalvar == 1);
	test(close_yunothread(thread) == 0);
	test(free_yunothread(thread) == 0);
}

void test_yunothread1 (){
	test1();
	test2();
	test3();
	test4();
}
