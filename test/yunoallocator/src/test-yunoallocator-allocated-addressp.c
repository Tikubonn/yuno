#include "test.h"
#include <yuno.private>

void test_yunoallocator_allocated_addressp (){
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
	test(yunoallocator_allocated_addressp(newaddr1, &example) == true);
	test(yunoallocator_allocated_addressp(newaddr2, &example) == true);
	test(yunoallocator_allocated_addressp(newaddr3, &example) == true);
	test(yunoallocator_allocated_addressp(buffer, &example) == true);
	test(yunoallocator_allocated_addressp(NULL, &example) == false);
	test(free_yunoallocator(newaddr1, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocator(newaddr2, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
	test(free_yunoallocator(newaddr3, sizeof(int), &example) == YUNOALLOCATOR_SUCCESS);
}
