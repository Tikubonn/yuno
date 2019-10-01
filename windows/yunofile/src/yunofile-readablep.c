#include <yuno.private>

bool __yunocall yunofile_readablep (yunofile *file){
	return (file->mode & YUNOFILE_READABLE) ? true : false;
}
