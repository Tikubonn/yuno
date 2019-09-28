#include <yuno.private>

bool __stdcall yunofile_readablep (yunofile *file){
	return (file->mode & YUNOFILE_READABLE) ? true : false;
}
