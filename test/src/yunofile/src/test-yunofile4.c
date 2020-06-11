#include <yuno.h>
#include <test.h>

#define UNEXIST_FILE "unexist.txt"

static void test1 (){
	yunofile file;
	nortice("file of " UNEXIST_FILE " must be unexist...");
	test(open_yunofile(UNEXIST_FILE, YUNOFILE_READABLE, NULL, 0, &file) != 0); // always error!
	test(get_yunoerror() == YUNODOES_NOT_EXIST);
}

static void test2 (){
	yunofile file;
	nortice("file of " UNEXIST_FILE " must be unexist...");
	test(open_yunofile(UNEXIST_FILE, YUNOFILE_READABLE | YUNOFILE_ASYNC, NULL, 0, &file) != 0); // always error!
	test(get_yunoerror() == YUNODOES_NOT_EXIST);
}

static void test3 (){
	nortice("file of " UNEXIST_FILE " must be unexist...");
	test(new_yunofile(UNEXIST_FILE, YUNOFILE_READABLE, 0) == NULL); // always error!
	test(get_yunoerror() == YUNODOES_NOT_EXIST);
}

static void test4 (){
	nortice("file of " UNEXIST_FILE " must be unexist...");
	test(new_yunofile(UNEXIST_FILE, YUNOFILE_READABLE | YUNOFILE_ASYNC, 0) == NULL); // always error!
	test(get_yunoerror() == YUNODOES_NOT_EXIST);
}

void test_yunofile4 (){
	test1();
	test2();
	test3();
	test4();
}
