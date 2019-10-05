#include "test.h"
#include <yuno.private>

void test_calculate_yunoallocator_size (){
	size_t size;
	size_t seqsize;
	size_t mapsize;
	calculate_yunoallocator_size(4096, 4096, &size, &seqsize, &mapsize);
	test(size <= 4096);
	test(mapsize < seqsize);
}
