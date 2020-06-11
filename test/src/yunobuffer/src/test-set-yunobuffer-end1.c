#include <yuno.h>
#include <test.h>

#define TEST_DATA "abcdef"

/*
	set_yunobuffer_end 関数の動作確認をします
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
	// バッファの読み込み位置を最初の位置に移動します
	{
		yunosize newoffset;
		test(seek_yunobuffer(0, YUNOBUFFER_BEGIN, &buffer, &newoffset) == 0);
		test(newoffset == 0);
	}
	// バッファの終端位置を上書きします
	{
		test(set_yunobuffer_end(3, &buffer) == 0);
	}
	// データを変更された終端位置まで読み込みます
	{
		char readarray[1024];
		yunosize readsize = read_yunobuffer(readarray, sizeof(readarray), &buffer);
		test(readsize == 3);
		for (yunosize index = 0; index < 3; index++){
			test(readarray[index] == TEST_DATA[index]);
		}
	}
}

void test_set_yunobuffer_end1 (){
	test1();
}
