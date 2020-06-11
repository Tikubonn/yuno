#include <yuno.h>
#include <stdbool.h>

bool yunofile_asyncp (yunofile *file){
	return file->asyncp == true;
}
