
# Multi Processing 

Yuno はマルチプロセシングに対応しています。

Yuno のマルチプロセシング機能を利用すると、複数の処理を並行に実行することができます。
Yuno のマルチプロセシング機能は、マルチスレッディングとは異なり、メモリの共有は行われません。
プロセス間で通信を行いたい場合には、[パイプ](yunopipe.md)または[共有メモリ](yunoshared-memory.md)の利用を検討してください。

下記の例では、大域変数を上書きするプロセスを作成・実行し、その結果を表示します。

```c
#include <yuno.h>
#include <stdio.h>

static int globalvar;

static int example (void *parameter){
  globalvar = 1;
  printf("globalvar in subprocess = %d\n", globalvar);
  // >> globalvar in subprocess = 1
  return 0;
}

int main (){
  globalvar = 0;
  yunoprocess *process = new_yunoprocess(example, NULL);
  start_yunoprocess(process);
  wait_yunoprocess(process);
  close_yunoprocess(process);
  free_yunoprocess(process);
  printf("globalvar in main process = %d\n", globalvar);
  // >> globalvar in main process = 0
  return 0;
}
```

## yunoentrypoint 

```c
typedef int (*yunoentrypoint)(void *parameter);
```

作成されたプロセスで実行される関数の型です。

## yunoprocess 

Yuno によって作成されたプロセスを管理する型です。

## make_yunoprocess, new_yunoprocess 

```c
int make_yunoprocess (yunoentrypoint entrypoint, void *parameter, yunoprocess *process);
yunoprocess *new_yunoprocess (yunoentrypoint entrypoint, void *parameter);
```

新規にプロセスを作成します。

この関数によって作成されるプロセスは以下の特徴を持っています。

- 現在のプロセスの、作成時点のグローバルなメモリ領域を継承します。
- 現在のプロセスの、作成時点のスタック領域を継承します。
- *allocate_yunomemory* 関数で確保された領域を継承します。
- *allocate_yunoshared_memory* 関数で確保された領域を共有します。
- 継承可能な「ファイル・プロセス・スレッド・ミューテックス・セマフォ」を継承します。
- 動的リンクライブラリ内のメモリ領域が継承されるかは未定義です。

*open_yunoprocess* 関数も *new_yunoprocess* 関数もどちらともプロセスを作成します。
*open_yunoprocess* 関数は作成されたプロセスを、引数 *process* に保存します。
*new_yunoprocess* 関数は作成されたプロセスを、動的に確保した領域に保存し、そのアドレスを返します。
*new_yunoprocess* 関数によって返されたプロセスは、不要になった際に *free_yunoprocess* 関数で解放する必要があります。

引数 *entrypoint* は作成されたプロセスで実行される関数のアドレスです。

引数 *parameter* は作成されたプロセスで実行される関数の引数です。

*open_yunoprocess* がプロセスの作成に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

*new_yunoprocess* がプロセスの作成に成功した場合、この関数は有効なアドレスを返します。
エラーが発生した場合、この関数は `NULL` を返します。

## start_yunoprocess

```c
int start_yunoprocess (yunoprocess *process);
```

プロセスを起動します。

引数 *process* は起動するプロセスです。
引数 *process* が現在のプロセスの場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

プロセスの起動に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## wait_yunoprocess

```c
int wait_yunoprocess (yunowait_mode waitmode, yunoprocess *process);
```

プロセスが終了するまで待機します。

引数 *waitmode* はこれらの定数のうちのいずれかを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFOREVER | 引数 *process* が終了するまでの間、プロセスを待機します。 | 
| YUNONOWAIT  | 引数 *process* が終了したか確認し、終了した場合には０を返します。引数 *process* が終了していない場合、この関数は失敗し *YUNOBUSY* エラーが設定されます。 | 

引数 *process* は待ち合わせる対象のプロセスです。
引数 *process* が現在のプロセスの場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

プロセスの終了を確認した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## close_yunoprocess

```c
int close_yunoprocess (yunoprocess*);
```

作成されたプロセスを解放します。

プロセスの解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## free_yunoprocess

```c
int free_yunoprocess (yunoprocess*);
```

*new_yunoprocess* 関数で確保されたメモリ領域を解放します。

メモリ領域の解放に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
