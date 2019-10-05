#include "test.h"
#include <yuno.private>
#include "yunobitarray.h"

void test_set_get_yunobitarray (){
	yunobitarray array;
	yunobyte arrayseq[2]; // 16
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	test(set_yunobitarray(1, 0, &array) == 0);
	test(set_yunobitarray(1, 2, &array) == 0);
	test(set_yunobitarray(1, 4, &array) == 0);
	test(set_yunobitarray(1, 8, &array) == 0);
	test(set_yunobitarray(1, 10, &array) == 0);
	test(set_yunobitarray(1, 12, &array) == 0);
	test(set_yunobitarray(1, 14, &array) == 0);
	test(set_yunobitarray(1, 16, &array) != 0);
	{
		int value;
		test(get_yunobitarray(0, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(1, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(2, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(3, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(4, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(5, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(6, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(7, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(8, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(9, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(10, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(11, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(12, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(13, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(14, &array, &value) == 0);
		test(value == 1);
	}
	{
		int value;
		test(get_yunobitarray(15, &array, &value) == 0);
		test(value == 0);
	}
	{
		int value;
		test(get_yunobitarray(16, &array, &value) != 0);
	}
}
