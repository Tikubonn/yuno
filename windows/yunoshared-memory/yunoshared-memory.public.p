#include <stdio.h>

yunoshared_memory *global_yunoshared_memory;

void *yunoshared_memory_initialized1;
void *yunoshared_memory_initialized2;
void *yunoshared_memory_initialized3;

/*
	allocate_yunoshared_memory/free_yunoshared_memory の内部で利用される初期化用のマクロです。
	このマクロはアプリケーション内で最初に実行された時のみ global_yunoshared_memory の値を NULL で初期化します。
	その後に第一引数に渡された formula を評価しその結果を返します。
	雑な仕組みなので一定の確率で失敗するかもしれません。
*/

#define after_init_yunoshared_memory(formula)\
(((yunoshared_memory_initialized1!=(void*)&yunoshared_memory_initialized3)||\
(yunoshared_memory_initialized2!=(void*)&yunoshared_memory_initialized3)?\
(yunoshared_memory_initialized3=(void*)&yunoshared_memory_initialized3),\
(yunoshared_memory_initialized2=(void*)&yunoshared_memory_initialized3),\
(yunoshared_memory_initialized1=(void*)&yunoshared_memory_initialized3),\
(global_yunoshared_memory=NULL):0),(formula))
