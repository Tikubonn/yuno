#include "test.h"
#include <yuno.private>

void test_free_yunoallocatorp (){
	yunobyte buffer[4096] = { 0 };
	size_t size;
	size_t seqsize;
	size_t mapsize;
	calculate_yunoallocator_size(sizeof(buffer), 4096, &size, &seqsize, &mapsize);
	yunoallocator example;
	init_yunoallocator(buffer, seqsize, buffer + seqsize, mapsize, &example);
	test(free_yunoallocatorp(&example) == true);
	void *newaddr1;
	test(allocate_yunoallocator(sizeof(int), &example, &newaddr1) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocatorp(&example) == false);
	test(free_yunoallocator(newaddr1, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocatorp(&example) == true);
}
