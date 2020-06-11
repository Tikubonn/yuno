#include <yuno.h>
#include <windows.h>

inline void init_yunoshared_memory (DWORD processid, HANDLE mappingfile, void *allocatorseq, yunosize allocatorsize, yunobitarray_element *bitarrayseq, yunosize bitarraysize, void *mappingaddress, DWORD mappingsize, yunoshared_memory *nextmemory, yunoshared_memory *memory){
	memory->processid = processid;
	memory->mappingfile = mappingfile;
	memory->mappingsize = mappingsize;
	memory->mappingaddress = mappingaddress;
	init_yunoallocator(allocatorseq, allocatorsize, bitarrayseq, bitarraysize, &(memory->allocator));
	memory->next = nextmemory;
}
