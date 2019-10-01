#include <yuno.private>

bool yunofile_readablep (yunofile *file){
  return (file->mode & YUNOFILE_READABLE) ? true : false;
}

