#include "test.h"
#include <yuno.private>
#include "yunobitarray.h"

void test_fill_yunobitarray (){
	yunobitarray array;
	yunobyte arrayseq[2] = { 0 }; // 16
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	test(fill_yunobitarray(1, 0, 8, &array) == 0);
	for (size_t index = 0; index < 8; index++){
		int value;
		test(get_yunobitarray(index, &array, &value) == 0);
		test(value == 1);
	}
	for (size_t index = 0; index < 8; index++){
		int value;
		test(get_yunobitarray(index + 8, &array, &value) == 0);
		test(value == 0);
	}
}
