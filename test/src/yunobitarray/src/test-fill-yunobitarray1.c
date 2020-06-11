#include <yuno.h>
#include <test.h>

#define ARRAY_SIZE 32
#define ARRAY_LENGTH (ARRAY_SIZE * YUNOBITARRAY_ELEMENT_BIT_LENGTH)

/*
	fill_yunobitarray 関数の動作確認を行います
*/

static void test1 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit array for test.
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(0, index, &array) == 0);
		}
		test(fill_yunobitarray(1, 32, 4, &array) == 0);
	}
	// ビット配列が書き込まれていない箇所を検証します
	{
		for (yunosize index = 0; index < 4; index++){
			int value;
			test(get_yunobitarray(index, &array, &value) == 0);
			test(value == 0);
		}
	}
	// ビット配列が正しく書き込まれたか検証します
	{
		for (yunosize index = 0; index < 32; index++){
			int value;
			test(get_yunobitarray(index + 4, &array, &value) == 0);
			test(value == 1);
		}
	}
	// ビット配列が書き込まれていない箇所を検証します
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 4 + 32; index < length; index++){
			int value;
			test(get_yunobitarray(index, &array, &value) == 0);
			test(value == 0);
		}
	}
}

/*
	fill_yunobitarray 関数の動作確認を行います
*/

static void test2 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit array for test.
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(1, index, &array) == 0);
		}
		test(fill_yunobitarray(0, 32, 4, &array) == 0);
	}
	// ビット配列が書き込まれていない箇所を検証します
	{
		for (yunosize index = 0; index < 4; index++){
			int value;
			test(get_yunobitarray(index, &array, &value) == 0);
			test(value == 1);
		}
	}
	// ビット配列が正しく書き込まれたか検証します
	{
		for (yunosize index = 0; index < 32; index++){
			int value;
			test(get_yunobitarray(index + 4, &array, &value) == 0);
			test(value == 0);
		}
	}
	// ビット配列が書き込まれていない箇所を検証します
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 4 + 32; index < length; index++){
			int value;
			test(get_yunobitarray(index, &array, &value) == 0);
			test(value == 1);
		}
	}
}

void test_fill_yunobitarray1 (){
	test1();
	test2();
}
