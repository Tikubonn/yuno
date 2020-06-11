#include <yuno.h>
#include <test.h>
#include <stddef.h>

#define TEST_DATA "abcdef"

/*
	yunobuffer の基本的な操作を検証します
*/

static void test1 (){
	char bufferarray[1024];
	yunobuffer buffer;
	init_yunobuffer(bufferarray, sizeof(bufferarray), &buffer);
	// 書き込み操作の動作確認
	{
		test(write_yunobuffer(TEST_DATA, sizeof(TEST_DATA) -1, &buffer) == sizeof(TEST_DATA) -1);
		test(tell_yunobuffer(&buffer) == sizeof(TEST_DATA) -1);
	}
	// バッファ位置操作の動作確認
	{
		yunosize newoffset;
		test(seek_yunobuffer(0, YUNOBUFFER_BEGIN, &buffer, &newoffset) == 0);
		test(newoffset == 0);
	}
	// 読み込み操作の動作確認
	{
		char readarray[1024];
		test(read_yunobuffer(readarray, sizeof(readarray), &buffer) == sizeof(TEST_DATA) -1);
		for (size_t index = 0; index < sizeof(TEST_DATA) -1; index++){
			test(readarray[index] == TEST_DATA[index]);
		}
	}
}

void test_yunobuffer1 (){
	test1();
}
