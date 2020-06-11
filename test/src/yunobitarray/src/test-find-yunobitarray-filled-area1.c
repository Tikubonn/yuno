#include <yuno.h>
#include <test.h>

#define ARRAY_SIZE 32
#define ARRAY_LENGTH (ARRAY_SIZE * YUNOBITARRAY_ELEMENT_BIT_LENGTH)
#define FILLED_SIZE 16

/*
	find_yunobitarray_filled_area 関数の動作確認を行います
*/

static void test1 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit-array for test.
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(0, index, &array) == 0);
		}
		for (yunosize index = 0; index < 8; index++){
			test(set_yunobitarray(1, index + 1, &array) == 0);
		}
		for (yunosize index = 0; index < FILLED_SIZE; index++){
			test(set_yunobitarray(1, index + 32 + 1, &array) == 0);
		}
		for (yunosize index = 0; index < FILLED_SIZE +8; index++){
			test(set_yunobitarray(1, index + 96 + 1, &array) == 0);
		}
	}
	// ビット配列の先頭から 1 の連続した領域を検索します
	yunosize indexfound1;
	{
		test(find_yunobitarray_filled_area(1, FILLED_SIZE, 0, &array, &indexfound1) == 0);
		test(indexfound1 == 32 + 1);
	}
	// 前回の検索位置から 1 の連続した領域を検索します
	yunosize indexfound2;
	{
		test(find_yunobitarray_filled_area(1, FILLED_SIZE, indexfound1 + FILLED_SIZE, &array, &indexfound2) == 0);
		test(indexfound2 == 96 + 1);
	}
	// 前回の検索位置から 1 の連続した領域を検索します
	yunosize indexfound3;
	{
		test(find_yunobitarray_filled_area(1, FILLED_SIZE, indexfound2 + FILLED_SIZE, &array, &indexfound3) != 0); // always not found!
	}
}

/*
	find_yunobitarray_filled_area 関数の動作確認を行います
*/

static void test2 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// setup bit-array for test.
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(1, index, &array) == 0);
		}
		for (yunosize index = 0; index < 8; index++){
			test(set_yunobitarray(0, index + 1, &array) == 0);
		}
		for (yunosize index = 0; index < FILLED_SIZE; index++){
			test(set_yunobitarray(0, index + 32 + 1, &array) == 0);
		}
		for (yunosize index = 0; index < FILLED_SIZE +8; index++){
			test(set_yunobitarray(0, index + 96 + 1, &array) == 0);
		}
	}
	// ビット配列の先頭から 0 の連続した領域を検索します
	yunosize indexfound1;
	{
		test(find_yunobitarray_filled_area(0, FILLED_SIZE, 0, &array, &indexfound1) == 0);
		test(indexfound1 == 32 + 1);
	}
	// 前回の検索位置から 0 の連続した領域を検索します
	yunosize indexfound2;
	{
		test(find_yunobitarray_filled_area(0, FILLED_SIZE, indexfound1 + FILLED_SIZE, &array, &indexfound2) == 0);
		test(indexfound2 == 96 + 1);
	}
	// 前回の検索位置から 0 の連続した領域を検索します
	yunosize indexfound3;
	{
		test(find_yunobitarray_filled_area(0, FILLED_SIZE, indexfound2 + FILLED_SIZE, &array, &indexfound3) != 0); // always not found!
	}
}

void test_find_yunobitarray_filled_area1 (){
	test1();
	test2();
}
