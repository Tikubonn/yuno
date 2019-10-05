#include <yuno.private>
#include <stddef.h>

void calculate_yunoallocator_size (size_t size, size_t pagesize, size_t *sizep, size_t *seqsizep, size_t *mapsizep){
	//size_t alignedsize = ALIGN_FOR_YUNOALLOCATOR(size, pagesize);
	size_t alignedsize = ALIGN_FOR_YUNOALLOCATOR(
		ALIGN_FOR_YUNOALLOCATOR(size, YUNOALLOCATOR_ALIGNMENT * YUNOBYTE_BIT_COUNT), // align to 64bytes
		pagesize
	);
	size_t mapsize = alignedsize / (YUNOALLOCATOR_ALIGNMENT * YUNOBYTE_BIT_COUNT);
	*sizep = alignedsize;
	*seqsizep = alignedsize - mapsize;
	*mapsizep = (alignedsize - mapsize) / (YUNOALLOCATOR_ALIGNMENT * YUNOBYTE_BIT_COUNT);
}
