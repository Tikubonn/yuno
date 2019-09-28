#include <yuno.private>

bool __stdcall yunofile_writablep (yunofile *file){
	return (file->mode & YUNOFILE_WRITABLE || file->mode & YUNOFILE_APPENDABLE) ? true : false;
}
