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
	yunothread thread;
	test(get_yunoerror() == YUNONOERROR);
	test(make_yunothread(entrypoint, NULL, &thread) == 0);
	test(start_yunothread(&thread) == 0);
	test(yunosleep(SLEEP_SECONDS, 0) == 0);
	printf("get_yunoerror=%d\n", get_yunoerror());
	test(get_yunoerror() == YUNONOERROR);
	test(wait_yunothread(YUNOFOREVER, &thread) == 0);
	test(close_yunothread(&thread) == 0);
}

static void test2 (){
	yunothread *thread = new_yunothread(entrypoint, NULL);
	test(thread != NULL);
	test(get_yunoerror() == YUNONOERROR);
	test(start_yunothread(thread) == 0);
	test(yunosleep(SLEEP_SECONDS, 0) == 0);
	test(get_yunoerror() == YUNONOERROR);
	test(wait_yunothread(YUNOFOREVER, thread) == 0);
	test(close_yunothread(thread) == 0);
	test(free_yunothread(thread) == 0);
}

void test_yunothread2 (){
	test1();
	test2();
}
