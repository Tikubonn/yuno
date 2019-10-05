#include <test.h>
#include <yuno.h>

int main (){
	init_yunoshared_memory();
	test_yunoprocess();
	test_yunothread();
	test_yunofile();
	test_yunomutex();
	test_yunopipe();
	test_yunosemaphore();
	test_yunoshared_memory();
	return 0;
}
