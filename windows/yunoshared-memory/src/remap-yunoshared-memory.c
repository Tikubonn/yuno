#include <yuno.h>
#include <windows.h>
#include <stdio.h>

inline int remap_yunoshared_memory (yunoshared_memory **memoryp){
	reset_yunoerror();
	for (yunoshared_memory *memory = *memoryp; memory != NULL; memory = memory->next){
		MEMORY_BASIC_INFORMATION meminfo;
		if (VirtualQuery(memory->mappingaddress, &meminfo, sizeof(meminfo)) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		if (meminfo.State == MEM_FREE){
			void *reserved = VirtualAlloc(meminfo.BaseAddress, memory->mappingsize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (reserved == NULL){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			else 
			if (reserved != memory->mappingaddress){
				set_yunoerror(YUNOERROR);
				return 1;
			}
			if (VirtualFree(reserved, 0, MEM_RELEASE) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
		}
		if (MapViewOfFileEx(memory->mappingfile, FILE_MAP_ALL_ACCESS, 0, 0, 0, memory->mappingaddress) == NULL){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
	}
	return 0;
}
