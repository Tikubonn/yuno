#include <yuno.h>
#include <test.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define BITARRAY_SIZE 128
#define ALLOCATOR_SIZE SCALE_FOR_YUNOALLOCATOR(BITARRAY_SIZE)

#define ALLOCATE_SIZE1 123
#define ALLOCATE_SIZE2 12
#define ALLOCATE_SIZE3 1234

/*
	free_yunoallocator 関数で解放された領域を再確保した場合の動作を検証します
*/

static void test1 (){
	yunobitarray_element bitarrayseq[BITARRAY_SIZE];
	char allocatorseq[ALLOCATOR_SIZE] = { 0 };
	yunoallocator allocator;
	init_yunoallocator(
		allocatorseq, 
		sizeof(allocatorseq), 
		bitarrayseq,
		sizeof(bitarrayseq) / sizeof(yunobitarray_element), 
		&allocator
	);
	// yunoallocator の初期状態が空であるか検証します
	{
		test(empty_yunoallocatorp(&allocator) == true);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated1;
	{
		allocated1 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated1 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated1[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated1[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated2;
	{
		allocated2 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated2 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated2[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated2[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 最初に確保した領域を解放します
	{
		test(free_yunoallocator(allocated1, ALLOCATE_SIZE1, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 解放された領域を再度確保します
	char *allocated3;
	{
		allocated3 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated3 != NULL);
		test(allocated3 == allocated1);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated3[index] == CHAR_MAX);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated3[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 確保された領域を解放します
	{
		test(free_yunoallocator(allocated2, ALLOCATE_SIZE1, &allocator) == 0);
		test(free_yunoallocator(allocated3, ALLOCATE_SIZE1, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == true);
	}
}

/*
	free_yunoallocator 関数で解放された領域を再確保した場合の動作を検証します
*/

static void test2 (){
	yunobitarray_element bitarrayseq[BITARRAY_SIZE];
	char allocatorseq[ALLOCATOR_SIZE] = { 0 };
	yunoallocator allocator;
	init_yunoallocator(
		allocatorseq, 
		sizeof(allocatorseq), 
		bitarrayseq,
		sizeof(bitarrayseq) / sizeof(yunobitarray_element), 
		&allocator
	);
	// yunoallocator の初期状態が空であるか検証します
	{
		test(empty_yunoallocatorp(&allocator) == true);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated1;
	{
		allocated1 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated1 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated1[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated1[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated2;
	{
		allocated2 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated2 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated2[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated2[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 最初に確保した領域を解放します
	{
		test(free_yunoallocator(allocated1, ALLOCATE_SIZE1, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 解放された領域を再度確保します
	char *allocated3;
	{
		allocated3 = allocate_yunoallocator(ALLOCATE_SIZE2, &allocator);
		test(allocated3 != NULL);
		test(allocated3 == allocated1);
		for (yunosize index = 0; index < ALLOCATE_SIZE2; index++){
			test(allocated3[index] == CHAR_MAX);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE2; index++){
			allocated3[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 確保された領域を解放します
	{
		test(free_yunoallocator(allocated2, ALLOCATE_SIZE1, &allocator) == 0);
		test(free_yunoallocator(allocated3, ALLOCATE_SIZE2, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == true);
	}
}

/*
	free_yunoallocator 関数で解放された領域を再確保した場合の動作を検証します
*/

static void test3 (){
	yunobitarray_element bitarrayseq[BITARRAY_SIZE];
	char allocatorseq[ALLOCATOR_SIZE] = { 0 };
	yunoallocator allocator;
	init_yunoallocator(
		allocatorseq, 
		sizeof(allocatorseq), 
		bitarrayseq,
		sizeof(bitarrayseq) / sizeof(yunobitarray_element), 
		&allocator
	);
	// yunoallocator の初期状態が空であるか検証します
	{
		test(empty_yunoallocatorp(&allocator) == true);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated1;
	{
		allocated1 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated1 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated1[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated1[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// yunoallocator から数バイト分の領域を確保します
	char *allocated2;
	{
		allocated2 = allocate_yunoallocator(ALLOCATE_SIZE1, &allocator);
		test(allocated2 != NULL);
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			test(allocated2[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE1; index++){
			allocated2[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 最初に確保した領域を解放します
	{
		test(free_yunoallocator(allocated1, ALLOCATE_SIZE1, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 解放された領域を再度確保します
	char *allocated3;
	{
		allocated3 = allocate_yunoallocator(ALLOCATE_SIZE3, &allocator);
		test(allocated3 != NULL);
		test(allocated3 != allocated1);
		for (yunosize index = 0; index < ALLOCATE_SIZE3; index++){
			test(allocated3[index] == 0);
		}
		for (yunosize index = 0; index < ALLOCATE_SIZE3; index++){
			allocated3[index] = CHAR_MAX;
		}
		test(empty_yunoallocatorp(&allocator) == false);
	}
	// 確保された領域を解放します
	{
		test(free_yunoallocator(allocated2, ALLOCATE_SIZE1, &allocator) == 0);
		test(free_yunoallocator(allocated3, ALLOCATE_SIZE3, &allocator) == 0);
		test(empty_yunoallocatorp(&allocator) == true);
	}
}

void test_yunoallocator2 (){
	test1();
	test2();
	test3();
}
