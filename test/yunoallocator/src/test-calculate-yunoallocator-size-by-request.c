#include "test.h"
#include <yuno.private>

void test_calculate_yunoallocator_size_by_request (){
	size_t size;
	size_t seqsize;
	size_t mapsize;
	calculate_yunoallocator_size_by_request(4096, 4096, &size, &seqsize, &mapsize);
	test(4096 < size);
	test(4096 <= seqsize);
	test(mapsize < seqsize);
}
