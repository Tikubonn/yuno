#include <yuno.h>
#include <test.h>

#define UNEXIST_FILE "unexist.txt"

static int entrypoint (void *parameter){
	(void)parameter; // ignore unused variable!
	yunofile file;
	nortice("file of " UNEXIST_FILE " must be unexist...");
	test(open_yunofile(UNEXIST_FILE, YUNOFILE_READABLE, NULL, 0, &file) != 0); // always error!
	test(get_yunoerror() == YUNODOES_NOT_EXIST);
	return 0;
}

#define SLEEP_SECONDS 3

static void test1 (){
	yunoprocess process;
	test(get_yunoerror() == YUNONOERROR);
	test(make_yunoprocess(entrypoint, NULL, &process) == 0);
	test(start_yunoprocess(&process) == 0);
	test(yunosleep(SLEEP_SECONDS, 0) == 0);
	test(get_yunoerror() == YUNONOERROR);
	test(wait_yunoprocess(YUNOFOREVER, &process) == 0);
	test(close_yunoprocess(&process) == 0);
}

static void test2 (){
	test(get_yunoerror() == YUNONOERROR);
	yunoprocess *process = new_yunoprocess(entrypoint, NULL);
	test(process != NULL);
	test(start_yunoprocess(process) == 0);
	test(yunosleep(SLEEP_SECONDS, 0) == 0);
	test(get_yunoerror() == YUNONOERROR);
	test(wait_yunoprocess(YUNOFOREVER, process) == 0);
	test(close_yunoprocess(process) == 0);
	test(free_yunoprocess(process) == 0);
}

void test_yunoprocess2 (){
	test1();
	test2();
}
