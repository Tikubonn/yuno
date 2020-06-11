
# Semaphore

Yuno はセマフォによる排他制御に対応しています。

セマフォを利用することで、並行処理を行う際に、それぞれのタスク間で同期をとることができます。

下記の例では、１秒間停止するスレッドを複数作成し、それらを３スレッド毎に実行させます。
このプログラムを実行すると、だいたい４秒後にプログラムが終了します。

```c
#include <yuno.h>

static int entrypoint (void *parameter){
  yunosemaphore *semaphore = parameter;
  wait_yunosemaphore(YUNOFOREVER, semaphore);
  yunosleep(1, 0);
  release_yunosemaphore(semaphore);
  return 0;
}

#define THREAD_COUNT 12

int main (){
  yunosemaphore *semaphore = new_yunosemaphore(3);
  yunothread *threades[THREAD_COUNT];
  for (size_t index = 0; index < THREAD_COUNT; index++){
    THREADes[index] = new_yunothread(entrypoint, semaphore);
  }
  for (size_t index = 0; index < THREAD_COUNT; index++){
    start_yunoTHREAD(threades[index]);
  }
  for (size_t index = 0; index < THREAD_COUNT; index++){
    wait_yunothread(YUNOFOREVER, threades[index]);
    close_yunothread(threades[index]);
    free_yunothread(threades[index]);
  }
  free_yunosemaphore(semaphore);
  return 0;
}
```

## yunosemaphore

作成されたセマフォを管理する型です。

## make_yunosemaphore, new_yunosemaphore

```c
int make_yunosemaphore (yunosize maxcount, yunosemaphore *semaphore);
yunosemaphore *new_yunosemaphore (yunosize maxcount);
```

新しいセマフォします。
どちらの関数もセマフォを作成します。
*make_yunosemaphore* 関数は作成したセマフォを引数 *semaphore* に保存します。
*new_yunosemaphore* 関数は作成したセマフォを、動的に確保した領域に保存し、そのアドレスを返します。
*new_yunosemaphore* 関数によって返されたアドレスは、不要になり次第 *free_yunosemaphore* 関数で解放する必要があります。

引数 *maxcount* はセマフォの最大所有者数です。

*make_yunosemaphore* 関数がセマフォの作成に成功すると、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

*new_yunosemaphore* 関数がセマフォの作成に成功すると、有効なアドレスを返します。
エラーが発生した場合、この関数は `NULL` を返します。

## wait_yunosemaphore

```c
int wait_yunosemaphore (yunosemaphore*);
```

セマフォの所有権が得られるまでの間、スレッドを待機します。

引数 *waitmode* はこれらの定数のうちのいずれかを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFOREVER | 引数 *semaphore* の所有権が得られるまでの間、スレッドを待機します。 | 
| YUNONOWAIT  | 引数 *semaphore* の所有権が得られるか確認し、得られるようであれば所有権を取得します。引数 *semaphore* がすべて占有されていた場合、この関数は失敗し *YUNOBUSY* エラーを設定します。 | 

セマフォの所有権を取得すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## release_yunosemaphore

```c
int release_yunosemaphore (yunosemaphore*);
```

*wait_yunosemaphore* 関数で所有権を得たセマフォを解放します。

セマフォの所有権を破棄すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## close_yunosemaphore

```c
int close_yunosemaphore (yunosemaphore*);
```

作成されたセマフォを解放します。

セマフォの解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## free_yunosemaphore

```c
int free_yunosemaphore (yunosemaphore*);
```

*new_yunosemaphore* 関数で確保されたメモリ領域を解放します。

メモリ領域の解放に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
