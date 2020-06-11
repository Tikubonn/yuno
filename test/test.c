#include <yuno.h>
#include <test.h>

int main (){
	setup_yuno();
	test_yunobuffer();
	test_yunobitarray();
	test_yunoallocator();
	test_yunofile();
	test_yunothread();
	test_yunoprocess();
	test_yunopipe();
	test_yunomemory();
	test_yunoshared_memory();
	test_yunotime();
	test_yunomutex();
	test_yunosemaphore();
	return 0;
}
