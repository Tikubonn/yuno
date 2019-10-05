#include "test.h"
#include <yuno.private>
#include "yunobitarray.h"

void test_yunobitarray_length (){
	yunobitarray array;
	yunobyte arrayseq[2] = { 0 }; // 16
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	test(yunobitarray_length(&array) == 16);
}
