#include <yuno.h>
#include <test.h>

#define ARRAY_SIZE 32
#define ARRAY_LENGTH (ARRAY_SIZE * YUNOBITARRAY_ELEMENT_BIT_LENGTH)
#define FAR_PLACE1 (YUNOBITARRAY_ELEMENT_BIT_LENGTH * 3 + 1)

/*
	find_yunobitarray 関数の動作確認を行います
*/

static void test1 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit-array like as (0 1 0 1 0 1 0 1 0...).
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(0, index, &array) == 0);
		}
		test(set_yunobitarray(1, 1, &array) == 0);
		test(set_yunobitarray(1, 3, &array) == 0);
		test(set_yunobitarray(1, 5, &array) == 0);
		test(set_yunobitarray(1, 7, &array) == 0);
		test(set_yunobitarray(1, FAR_PLACE1, &array) == 0);
	}
	// find_yunobitarray 関数で先頭から 1 を検索します
	yunosize indexfound1;
	{
		test(find_yunobitarray(1, 0, &array, &indexfound1) == 0);
		test(indexfound1 == 1);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound2;
	{
		test(find_yunobitarray(1, indexfound1 +1, &array, &indexfound2) == 0);
		test(indexfound2 == 3);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound3;
	{
		test(find_yunobitarray(1, indexfound2 +1, &array, &indexfound3) == 0);
		test(indexfound3 == 5);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound4;
	{
		test(find_yunobitarray(1, indexfound3 +1, &array, &indexfound4) == 0);
		test(indexfound4 == 7);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound5;
	{
		test(find_yunobitarray(1, indexfound4 +1, &array, &indexfound5) == 0);
		test(indexfound5 == FAR_PLACE1);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound6;
	{
		test(find_yunobitarray(1, indexfound5 +1, &array, &indexfound6) != 0); // always not found!
	}
}

/*
	find_yunobitarray 関数の動作確認を行います
*/

static void test2 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit-array like as (1 0 1 0 1 0 1 0 1...).
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(1, index, &array) == 0);
		}
		test(set_yunobitarray(0, 1, &array) == 0);
		test(set_yunobitarray(0, 3, &array) == 0);
		test(set_yunobitarray(0, 5, &array) == 0);
		test(set_yunobitarray(0, 7, &array) == 0);
		test(set_yunobitarray(0, FAR_PLACE1, &array) == 0);
	}
	// find_yunobitarray 関数で先頭から 1 を検索します
	yunosize indexfound1;
	{
		test(find_yunobitarray(0, 0, &array, &indexfound1) == 0);
		test(indexfound1 == 1);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound2;
	{
		test(find_yunobitarray(0, indexfound1 +1, &array, &indexfound2) == 0);
		test(indexfound2 == 3);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound3;
	{
		test(find_yunobitarray(0, indexfound2 +1, &array, &indexfound3) == 0);
		test(indexfound3 == 5);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound4;
	{
		test(find_yunobitarray(0, indexfound3 +1, &array, &indexfound4) == 0);
		test(indexfound4 == 7);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound5;
	{
		test(find_yunobitarray(0, indexfound4 +1, &array, &indexfound5) == 0);
		test(indexfound5 == FAR_PLACE1);
	}
	// find_yunobitarray 関数で前回の検索位置から 1 を検索します
	yunosize indexfound6;
	{
		test(find_yunobitarray(0, indexfound5 +1, &array, &indexfound6) != 0); // always not found!
	}
}

void test_find_yunobitarray1 (){
	test1();
	test2();
}
