
# Mutex

Yuno はミューテックスによる排他制御に対応しています。

ミューテックスを利用することで、並行処理を行う際に、それぞれのタスク間で同期をとることができます。
これにより、特定の処理の不可分性を保証したり、メモリ競合を回避することができます。

下記の例では複数のスレッドを作成し、
それぞれのスレッドで同期をとりながらグローバル変数 *countup* をインクリメントしています。

```c
#include <yuno.h>
#include <stdio.h>

static int countup;

static int entrypoint (void *parameter){
  yunomutex *mutex = parameter;
  wait_yunomutex(YUNOFOREVER, mutex);
  countup += 1;
  release_yunomutex(mutex);
  return 0;
}

#define YUNOTHREAD_COUNT 3

int main (){
  countup = 0;
  yunomutex *mutex = new_yunomutex();
  yunothread *threads[YUNOTHREAD_COUNT];
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    threads[index] = new_yunothread(entrypoint, mutex);
  }
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    start_yunothread(threads[index]);
  }
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    wait_yunothread(YUNOFOREVER, threads[index]);
    close_yunothread(threads[index]);
    free_yunothread(threads[index]);
  }
  printf("countup = %d\n", countup);
  // >> countup = 3
  free_yunomutex(mutex);
  return 0;
}
```

## yunomutex

作成されたミューテックスを管理する型です。

## make_yunomutex, open_yunomutex

```c
int make_yunomutex (yunomutex *mutex);
yunomutex *new_yunomutex ();
```

新しいミューテックスを作成します。
どちらの関数もミューテックスを作成します。
*make_yunomutex* 関数は作成したミューテックスを引数 *mutex* に保存します。
*new_yunomutex* 関数は作成したミューテックスを、動的に確保した領域に保存し、そのアドレスを返します。
*new_yunomutex* 関数によって返されたアドレスは、不要になり次第 *free_yunomutex* 関数で解放する必要があります。

*make_yunomutex* 関数がミューテックスの作成に成功すると、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

*new_yunomutex* 関数がミューテックスの作成に成功すると、有効なアドレスを返します。
エラーが発生した場合、この関数は `NULL` を返します。

## wait_yunomutex

```c
int wait_yunomutex (yunowait_mode waitmode, yunomutex *mutex);
```

ミューテックスの所有権が得られるまでの間、スレッドを待機します。

引数 *waitmode* はこれらの定数のうちのいずれかを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFOREVER | 引数 *mutex* の所有権が得られるまでの間、スレッドを待機します。 | 
| YUNONOWAIT  | 引数 *mutex* の所有権が得られるか確認し、得られるようであれば所有権を取得します。引数 *mutex* が既に独占されていた場合、この関数は失敗し *YUNOBUSY* エラーを設定します。 | 

ミューテックスの所有権を取得すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## release_yunomutex

```c
int release_yunomutex (yunomutex *mutex);
```

*wait_yunomutex* 関数で所有権を得たミューテックスを解放します。

ミューテックスの所有権を破棄すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## close_yunomutex

```c
int close_yunomutex (yunomutex *mutex);
```

作成されたミューテックスを解放します。

ミューテックスの解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## free_yunomutex

```c
int free_yunomutex (yunomutex *mutex);
```

*new_yunomutex* 関数で確保されたメモリ領域を解放します。

メモリ領域の解放に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
