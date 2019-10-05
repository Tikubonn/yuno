#include "test.h"
#include <yuno.private>

void test_allocate_yunoallocator (){
	yunobyte buffer[4096] = { 0 };
	size_t size;
	size_t seqsize;
	size_t mapsize;
	calculate_yunoallocator_size(sizeof(buffer), 4096, &size, &seqsize, &mapsize);
	yunoallocator example;
	init_yunoallocator(buffer, seqsize, buffer + seqsize, mapsize, &example);
	void *newaddr1;
	test(allocate_yunoallocator(sizeof(int), &example, &newaddr1) == YUNOALLOCATOR_SUCCESS);
	void *newaddr2;
	test(allocate_yunoallocator(sizeof(int), &example, &newaddr2) == YUNOALLOCATOR_SUCCESS);
	void *newaddr3;
	test(allocate_yunoallocator(sizeof(int), &example, &newaddr3) == YUNOALLOCATOR_SUCCESS);
	void *newaddr4;
	test(allocate_yunoallocator(4096, &example, &newaddr4) == YUNOALLOCATOR_NOT_ENOUGH_MEMORY);	
	test(free_yunoallocator(newaddr1, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	void *newaddr5;
	test(allocate_yunoallocator(sizeof(int), &example, &newaddr5) == YUNOALLOCATOR_SUCCESS);
	test(newaddr1 == newaddr5);
	test(free_yunoallocator(newaddr2, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocator(newaddr3, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	//test(free_yunoallocator(newaddr4, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocator(newaddr5, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
}
