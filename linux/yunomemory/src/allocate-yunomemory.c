#include <yuno.h>
#include <stdlib.h>

/*
	brk および sbrk 関数は副作用があり
	他のライブラリに影響を及ぼす可能性があるため
	標準ライブラリの malloc 関数をそのまま使用しています
*/

void *allocate_yunomemory (yunosize size){
	reset_yunoerror();
	void *allocated = malloc(size);
	if (allocated == NULL){
		set_yunoerror(YUNOOS_ERROR);
		return NULL;
	}
	return allocated;
}
