#include <yuno.h>
#include <stdlib.h>

/*
	brk および sbrk 関数は副作用があり
	他のライブラリに影響を及ぼす可能性があるため
	標準ライブラリの free 関数をそのまま使用しています
*/

int free_yunomemory (void *address, yunosize size){
	(void)size; // ignore unused variable!
	reset_yunoerror();
	free(address);
	return 0;
}
