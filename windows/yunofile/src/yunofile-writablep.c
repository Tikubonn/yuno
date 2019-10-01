#include <yuno.private>

bool __yunocall yunofile_writablep (yunofile *file){
	return (file->mode & YUNOFILE_WRITABLE || file->mode & YUNOFILE_APPENDABLE) ? true : false;
}
