#include <yuno.h>
#include <stdbool.h>

#define BOOLEAN(value) ((value)? true: false)

bool yunofile_readablep (yunofile *file){
	return BOOLEAN(file->mode & YUNOFILE_READABLE);
}
