#include <yuno.h>
#include <test.h>
#include <time.h>
#include <math.h>

#define SLEEP_TIME 3

static void test1 (){
	yunoseconds time1;
	test(yunotime(&time1) == 0);
	test(yunosleep(SLEEP_TIME, 0) == 0);
	yunoseconds time2;
	test(yunotime(&time2) == 0);
	test(time2 - time1 == SLEEP_TIME);
}

#define DIFFERENCE_THRESHOLD 3

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)<(b)?(b):(a))

static void test2 (){
	time_t timewithtime;
	test(time(&timewithtime) != (time_t)-1);
	yunoseconds timewithyunotime;
	test(yunotime(&timewithyunotime) == 0);
	test(labs(timewithyunotime - timewithtime) <= DIFFERENCE_THRESHOLD);
}

void test_yunotime1 (){
	test1();
	test2();
}
