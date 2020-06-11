#include <yuno.h>
#include <test.h>
#include <stddef.h>

static void test1 (){
	int *newinteger1;
	{
		newinteger1 = allocate_yunoshared_memory(sizeof(int));
		test(newinteger1 != NULL);
		*newinteger1 = 1;
	}
	int *newinteger2;
	{
		newinteger2 = allocate_yunoshared_memory(sizeof(int));
		test(newinteger2 != NULL);
		test(newinteger2 != newinteger1);
		*newinteger2 = 2;
	}
	int *newinteger3;
	{
		newinteger3 = allocate_yunoshared_memory(sizeof(int));
		test(newinteger3 != NULL);
		test(newinteger3 != newinteger1);
		test(newinteger3 != newinteger2);
		*newinteger3 = 3;
	}
	{
		test(*newinteger1 == 1);
		test(*newinteger2 == 2);
		test(*newinteger3 == 3);
	}
	{
		test(free_yunoshared_memory(newinteger1, sizeof(int)) == 0);
		test(free_yunoshared_memory(newinteger2, sizeof(int)) == 0);
		test(free_yunoshared_memory(newinteger3, sizeof(int)) == 0);
	}
}

#define ARRAY_LENGTH 4096

static void test2 (){
	char *newarray = allocate_yunoshared_memory(ARRAY_LENGTH);
	test(newarray != NULL);
	for (size_t index = 0; index < ARRAY_LENGTH; index++){
		newarray[index] = (char)(index & 0xff);
	}
	for (size_t index = 0; index < ARRAY_LENGTH; index++){
		test(newarray[index] == (char)(index & 0xff));
	}
	test(free_yunoshared_memory(newarray, ARRAY_LENGTH) == 0);
}

void test_yunoshared_memory1 (){
	test1();
	test2();
}
