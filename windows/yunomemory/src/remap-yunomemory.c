#include <yuno.h>
#include <windows.h>

#define BUFFER_SIZE 4096

#define MIN(a, b) ((a)<(b)?(a):(b))

static inline int copy_memory (void *baseaddr, yunosize size, HANDLE processfrom, HANDLE processto){
	reset_yunoerror();
	char buffer[BUFFER_SIZE];
	for (yunosize offsetread = 0; offsetread < size;){
		SIZE_T readsize;
		if (ReadProcessMemory(processfrom, baseaddr + offsetread, buffer, MIN(sizeof(buffer), size - offsetread), &readsize) == 0){
			set_yunoerror(YUNOOS_ERROR);
			return 1;
		}
		for (yunosize offsetwrote = 0; offsetwrote < readsize;){
			SIZE_T wrotesize;
			if (WriteProcessMemory(processto, baseaddr + offsetread + offsetwrote, buffer + offsetwrote, readsize - offsetwrote, &wrotesize) == 0){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			offsetwrote += wrotesize;
		}
		offsetread += readsize;
	}
	return 0;
}

inline int remap_yunomemory (HANDLE process, yunomemory **globalmemoryp){
	reset_yunoerror();
	HANDLE currentprocess = GetCurrentProcess();
	for (yunomemory *memory = *globalmemoryp; memory != NULL; memory = memory->next){
		{
			void *reserved = VirtualAllocEx(process, memory->sequence, memory->size, MEM_RESERVE, PAGE_NOACCESS);
			if (reserved == NULL){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			else 
			if (reserved != memory->sequence){
				set_yunoerror(YUNOERROR);
				return 1;
			}
			void *committed = VirtualAllocEx(process, reserved, memory->size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (committed == NULL){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			else 
			if (committed != memory->sequence){
				set_yunoerror(YUNOERROR);
				return 1;
			}
			if (copy_memory(memory->sequence, memory->size, currentprocess, process) != 0){
				return 1;
			}
		}
		{
			void *reserved = VirtualAllocEx(process, memory->bitarrayseq, memory->bitarraysize, MEM_RESERVE, PAGE_NOACCESS);
			if (reserved == NULL){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			else 
			if (reserved != memory->bitarrayseq){
				set_yunoerror(YUNOERROR);
				return 1;
			}
			void *committed = VirtualAllocEx(process, reserved, memory->bitarraysize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (committed == NULL){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			else 
			if (committed != memory->bitarrayseq){
				set_yunoerror(YUNOERROR);
				return 1;
			}
			if (copy_memory(memory->bitarrayseq, memory->bitarraysize, currentprocess, process) != 0){
				return 1;
			}
		}
	}
	return 0;
}
