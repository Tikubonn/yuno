#include <yuno.h>
#include <test.h>

#define TEST_DATA "abcdef"

/*
	clear_yunobuffer 関数の動作確認を行います
*/

static void test1 (){
	char bufferarray[1024];
	yunobuffer buffer;
	init_yunobuffer(bufferarray, sizeof(bufferarray), &buffer);
	// 検証のために適当なデータをバッファに書き込みます
	{
		test(write_yunobuffer(TEST_DATA, sizeof(TEST_DATA) -1, &buffer) == sizeof(TEST_DATA) -1);
		test(tell_yunobuffer(&buffer) == sizeof(TEST_DATA) -1);
	}
	// バッファを消去します
	{
		clear_yunobuffer(&buffer);
		test(tell_yunobuffer(&buffer) == 0);
	}
	// バッファを消去後の読み込み操作を検証します
	{
		char readarray[1024];
		test(read_yunobuffer(readarray, sizeof(readarray), &buffer) == 0);
	}
}

void test_clear_yunobuffer1 (){
	test1();
}
