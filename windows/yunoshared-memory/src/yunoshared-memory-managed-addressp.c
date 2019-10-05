#include <yuno.private>
#include <stddef.h>
#include <stdbool.h>

bool yunoshared_memory_managed_addressp (void *address, yunoshared_memory **sharedmemoryp){
	for (yunoshared_memory *memory = *sharedmemoryp; memory != NULL; memory = memory->next){
		if (memory->address <= address && 
			 	address < memory->address + memory->size){
			return true;
		}
	}
	return false;
}
