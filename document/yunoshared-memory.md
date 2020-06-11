
# Shared Memory Allocation 

Yuno は共有メモリに対応しています。

```c
#include <yuno.h>
#include <stdio.h>

static int entrypoint (void *parameter){
  int *sharedint = parameter;
  *sharedint = 1;
  sync_yunoshared_memory(sharedint);
  return 0;
}

int main (){
  int *sharedint = allocate_yunoshared_memory(sizeof(int));
  *sharedint = 0;
  yunoprocess *process = new_yunoprocess(entrypoint, sharedint);
  start_yunoprocess(process);
  wait_yunoprocess(YUNOFOREVER, process);
  printf("sharedint=%d\n", *sharedint); // sharedint=1
  close_yunoprocess(process);
  free_yunoprocess(process);
  return 0;
}
```

## allocate_yunoshared_memory 

```c
void *allocate_yunoshared_memory (yunosize size);
```

読み書き可能な共有メモリを動的に確保します。

この関数によって確保されたメモリ領域はプロセス間で共有されます。
ただし、プロセス作成後に確保された領域は確保されません。
この関数によって確保された領域への変更は、
*async-yunoshared-memory* 関数が実行されるまで、
他のプロセスに反映されない可能性があります。

引数 *size* は確保する領域のサイズです。
この値は必ず０よりも大きくなくてはなりません。
もし引数 *size* が０以下の値を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

メモリ領域の確保に成功すると、この関数は確保した領域の先頭アドレスを返します。
十分な大きさのメモリ領域が確保できなかった場合、この関数は失敗し、*YUNONOT_ENOUGH_MEMOTY* エラーを設定します。
エラーが発生した場合、この関数は `NULL` を返します。

## async_yunoshared_memory 

```c
int async_yunoshared_memory (void *address);
```

確保されたメモリ領域への変更を、他のプロセスに反映させます。

引数 *address* は変更があったメモリ領域を指すアドレスです。

変更を他プロセスに反映出来た場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## free_yunoshared_memory 

```c
int free_yunoshared_memory (void *address, yunosize size);
```

確保されたメモリ領域を解放します。

この関数は *allocate_yunoshared_memory* 関数で確保されたメモリ領域を解放します。

引数 *address* は *allocate_yunoshared_memory* 関数で返されたアドレスです。
引数 *address* が *allocate_yunoshared_memory* 関数で返されたアドレスでない場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。
引数 *address* が既に解放済みの領域を指していた場合、動作は未定義です。

引数 *size* は *allocate_yunoshared_memory* 関数で要求したメモリ領域のサイズです。
この値が *allocate_yunoshared_memory* 関数で要求したメモリ領域のサイズと異なる場合、動作は未定義です。

確保されたメモリ領域の解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は `NULL` を返します。
