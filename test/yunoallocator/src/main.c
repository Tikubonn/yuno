#include "test.h"
#include <yuno.private>
#include "yunoallocator.h"

void main (){
	test_calculate_yunoallocator_size();
	test_calculate_yunoallocator_size_by_request();
	test_allocate_yunoallocator();
	test_free_yunoallocatorp();
	test_yunoallocator_allocated_addressp();
}
