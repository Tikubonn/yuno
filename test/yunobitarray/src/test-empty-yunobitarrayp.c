#include "test.h"
#include <yuno.private>
#include "yunobitarray.h"

void test_empty_yunobitarrayp (){
	yunobitarray array;
	yunobyte arrayseq[2] = { 0 }; // 16
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	test(empty_yunobitarrayp(&array) == true);
	test(set_yunobitarray(1, 0, &array) == 0);
	test(empty_yunobitarrayp(&array) == false);
}
