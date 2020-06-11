
# Multi Threading

Yuno はマルチスレッディングに対応しています。

Yuno のマルチスレッディング機能を利用すると、複数の処理を並行に実行することができます。
Yuno のマルチスレッディング機能は、マルチプロセシングとは異なり、スタック領域を除く、すべての記憶領域を共有します。
メモリ競合を回避したい場合には、[ミューテックス](yunomutex.md)または[セマフォ](yunosemaphore.md)の利用を検討してください。

下記の例では、大域変数を上書きするスレッドを作成・実行し、その結果を表示します。

```c
#include <yuno.h>
#include <stdio.h>

static int globalvar;

static int example (void *parameter){
  globalvar = 1;
  printf("globalvar in subthread = %d\n", globalvar);
  // >> globalvar in subthread = 1
  return 0;
}

int main (){
  globalvar = 0;
  yunothread *thread = new_yunothread(example, NULL);
  start_yunothread(thread);
  wait_yunothread(thread);
  close_yunothread(thread);
  free_yunothread(thread);
  printf("globalvar in main thread = %d\n", globalvar);
  // >> globalvar in main thread = 1
  return 0;
}
```

## yunoentrypoint 

```c
typedef int (*yunoentrypoint)(void *parameter);
```

作成されたスレッドで実行される関数の型です。

## yunothread 

Yuno によって作成されたスレッドを管理する型です。

## make_yunothread, new_yunothread 

```c
int make_yunothread (yunoentrypoint entrypoint, void *parameter, yunothread *thread);
yunothread *new_yunothread (yunoentrypoint entrypoint, void *parameter);
```

新規にスレッドを作成します。

*open_yunothread* 関数も *new_yunothread* 関数もどちらともスレッドを作成します。
*open_yunothread* 関数は作成されたスレッドを、引数 *thread* に保存します。
*new_yunothread* 関数は作成されたスレッドを、動的に確保した領域に保存し、そのアドレスを返します。
*new_yunothread* 関数によって返されたスレッドは、不要になった際に *free_yunothread* 関数で解放する必要があります。

引数 *entrypoint* は作成されたスレッドで実行される関数のアドレスです。

引数 *parameter* は作成されたスレッドで実行される関数の引数です。

*open_yunothread* がスレッドの作成に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

*new_yunothread* がスレッドの作成に成功した場合、この関数は有効なアドレスを返します。
エラーが発生した場合、この関数は `NULL` を返します。

## start_yunothread

```c
int start_yunothread (yunothread *thread);
```

スレッドを起動します。

引数 *thread* は起動するスレッドです。
引数 *thread* が現在のスレッドの場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

スレッドの起動に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## wait_yunothread

```c
int wait_yunothread (yunowait_mode waitmode, yunothread *thread);
```

スレッドが終了するまで待機します。

引数 *waitmode* はこれらの定数のうちのいずれかを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFOREVER | 引数 *thread* が終了するまでの間、スレッドを待機します。 | 
| YUNONOWAIT  | 引数 *thread* が終了したか確認し、終了した場合には０を返します。引数 *thread* が終了していない場合、この関数は失敗し *YUNOBUSY* エラーが設定されます。 | 

引数 *thread* は待ち合わせる対象のスレッドです。
引数 *thread* が現在のスレッドの場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

スレッドの終了を確認した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## close_yunothread

```c
int close_yunothread (yunothread*);
```

作成されたスレッドを解放します。

スレッドの解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## free_yunothread

```c
int free_yunothread (yunothread*);
```

*new_yunothread* 関数で確保されたメモリ領域を解放します。

メモリ領域の解放に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
