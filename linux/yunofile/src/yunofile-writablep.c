#include <yuno.h>
#include <stdbool.h>

#define BOOLEAN(value) ((value)? true: false)

bool yunofile_writablep (yunofile *file){
	return BOOLEAN(file->mode & YUNOFILE_WRITABLE);
}
