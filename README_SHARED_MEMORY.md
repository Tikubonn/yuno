
# Shared Memory

Yuno はプロセス間での共有メモリをサポートしています。

下記の例ではメインプロセスで **int** の大きさの共有メモリを確保した後に、サブプロセス側でメモリの内容を書き換えています。
メモリはプロセス間で共有されているため、サブプロセス側で書き換えられた内容がそのままメインプロセスにも反映されています。

```c
#include <yuno.h>
#include <stdio.h>

int __yunocall example (void *parameter){
  int *sharedint = parameter;
  *sharedint = 1;
  printf("sharedint in subprocess = %d\n", *sharedint);
  // >> sharedint in subprocess = 1
  return 0;
}

int main (){
  int *sharedint = allocate_yunoshared_memory(sizeof(int));
  *sharedint = 0;
  yunoprocess *process = make_yunoprocess(example, sharedint);
  start_yunoprocess(process);
  wait_yunoprocess(YUNOPROCESS_FOREVER, process);
  close_yunoprocess(process);
  free_yunoprocess(process);
  printf("sharedint in main process = %d\n", *sharedint);
  // >> sharedint in main process = 1
  free_yunoshared_memory(sharedint, sizeof(int));
  return 0;
}

```

## allocate_yunoshared_memory

```c
void *allocate_yunoshared_memory (size_t size);
```

要求された大きさを満たすプロセス間で共有可能なメモリ領域を確保します。
要求するメモリ領域の大きさは `0` よりも大きくなくてはなりません。
さもなければこのサブルーチンは即座に失敗するでしょう。
このサブルーチンは成功した場合には確保されたメモリ領域の最初のアドレスを返します。
失敗した場合にはこのサブルーチンは **NULL** を返します。

※このサブルーチンは環境によってマクロであったり関数であったり定義が異なります。
そのためこのサブルーチンを関数の引数に利用したりすることは推奨できません。
もし仮にこのサブルーチンをそのように使いたい場合には別途でこの関数のラッパー関数を定義し、
その関数のアドレスを与えると良いでしょう。

## free_yunoshared_memory

```c
yunoshared_memory_status free_yunoshared_memory (void *address, size_t size);
```

[allocate_yunoshared_memory](#allocate_yunoshared_memory) サブルーチンで確保されたメモリ領域を解放します。
第２引数は確保されているメモリ領域の大きさです。
このサブルーチンは成功した場合には **YUNOSHARED_MEMORY_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

※このサブルーチンは環境によってマクロであったり関数であったり定義が異なります。
そのためこのサブルーチンを関数の引数に利用したりすることは推奨できません。
もし仮にこのサブルーチンをそのように使いたい場合には別途でこの関数のラッパー関数を定義し、
その関数のアドレスを与えると良いでしょう。
