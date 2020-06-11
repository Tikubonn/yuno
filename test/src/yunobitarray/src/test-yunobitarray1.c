#include <yuno.h>
#include <test.h>

#define ARRAY_SIZE 32
#define ARRAY_LENGTH (ARRAY_SIZE * YUNOBITARRAY_ELEMENT_BIT_LENGTH)

/*
	ビット配列を扱う関数の動作確認を行います
*/

static void test1 (){
	yunobitarray_element arrayseq[ARRAY_SIZE];
	yunobitarray array;
	init_yunobitarray(arrayseq, sizeof(arrayseq), &array);
	// 初期化したビット配列の長さを検証します
	{
		test(yunobitarray_length(&array) == ARRAY_LENGTH);
		test(yunobitarray_size(&array) == ARRAY_SIZE);
	}
	// ビット配列の偶数要素に 1 を代入します
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			test(set_yunobitarray(index % 2, index, &array) == 0);
		}
	}
	// ビット配列が正常に書き込まれたか検証します
	{
		yunosize length = yunobitarray_length(&array);
		for (yunosize index = 0; index < length; index++){
			int value;
			test(get_yunobitarray(index, &array, &value) == 0);
			test(value == (int)(index % 2));
		}
	}
}

void test_yunobitarray1 (){
	test1();
}
