#include <yuno.h>
#include <test.h>

#define TEST_DATA "abcdef"

/*
	seek_yunobuffer 関数の動作確認をします
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
	// バッファの最初の位置から 3 進んだ位置にバッファポインタを設定します
	{
		yunosize newoffset;
		test(seek_yunobuffer(3, YUNOBUFFER_BEGIN, &buffer, &newoffset) == 0);
		test(newoffset == 3);
	}
	// バッファの現在の位置から 3 進んだ位置にバッファポインタを設定します
	{
		yunosize newoffset;
		test(seek_yunobuffer(3, YUNOBUFFER_CURRENT, &buffer, &newoffset) == 0);
		test(newoffset == 6);
	}
	// バッファの最期の位置から 3 進んだ位置にバッファポインタを設定します
	{
		yunosize newoffset;
		test(seek_yunobuffer(3, YUNOBUFFER_END, &buffer, &newoffset) == 0);
		test(newoffset == sizeof(TEST_DATA) -1 +3);
	}
}

void test_seek_yunobuffer1 (){
	test1();
}
