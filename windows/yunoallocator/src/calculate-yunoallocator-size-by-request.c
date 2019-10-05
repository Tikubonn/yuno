#include <yuno.private>
#include <stddef.h>

void calculate_yunoallocator_size_by_request (size_t size, size_t pagesize, size_t *sizep, size_t *seqsizep, size_t *mapsizep){
	size_t seqsize = ALIGN_FOR_YUNOALLOCATOR(size, YUNOALLOCATOR_ALIGNMENT);
	size_t mapsize = seqsize / YUNOALLOCATOR_ALIGNMENT * YUNOBYTE_BIT_COUNT;
	calculate_yunoallocator_size(seqsize + mapsize, pagesize, sizep, seqsizep, mapsizep);
}
