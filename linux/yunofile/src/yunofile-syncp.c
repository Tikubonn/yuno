#include <yuno.h>
#include <stdbool.h>

bool yunofile_syncp (yunofile *file){
	return file->asyncp == false;
}
