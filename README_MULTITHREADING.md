
# MultiThreading 

Yuno はマルチスレッディングにも対応しています。

マルチスレッディングはマルチプロセシングのように並行で処理を実行しますが、メモリを共有している部分が異なります。
そのため、複数のスレッドで同時に同じデータを書き換えたりした場合には、データを破壊してしまう恐れがあります。
それらを回避したい場合には [yunomutex](README_MUTEX.md) や [yunosemaphore](README_SEMAPHORE.md) など Yuno が提供している排他制御の機構を検討することをお勧めします。

```c
#include <yuno.h>
#include <stdio.h>

static int global_number;

static int example (void *parameter){
  global_number = 1;
  printf("global_number in subthread = %d\n", global_number);
  // >> global_number in subthread = 1
  return 0;
}

int main (){
  global_number = 0;
  yunothread *thread = make_yunothread(example, NULL);
  start_yunothread(thread);
  wait_yunothread(thread);
  close_yunothread(thread);
  free_yunothread(thread);
  printf("global_number in main thread = %d\n", global_number);
  // >> global_number in main thread = 1
  return 0;
}
```

## make_yunothread_manually

```c
yunothread_status make_yunothread_manually (yunothread_entry_point entrypoint, void *parameter, yunothread *thread);
```

複製先のスレッドで実行する関数とその引数を受け取り新規にサブスレッドを作成します。
作成されたスレッドは第三引数に保存されます。
作成されたサブスレッドは作成後すぐには実行されず、[start_yunothread](#start_yunothread) 関数が実行されるまで停止した状態になります。
スレッド自体は作成されているので、作成後は [close_yunothread](#close_yunothread) 関数で資源を解放してください。
この関数は成功すると **YUNOPROCESS_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## make_yunothread

```c
yunothread *make_yunothread (yunothread_entry_point entrypoint, void *parameter);
```

この関数は [make_yunothread_manually](#make_yunothread_manually) と同様に新規にサブスレッドを作成しますが、
作成されたサブスレッドを `malloc` で確保された領域に保存し、その領域を返り値として返します。
この関数によって作成された [yunothread](#yunothread) ポインタは不要になった場合に [free_yunothread](#free_yunothread) 関数で解放する必要があります。
この関数は成功した場合には新規の有効な [yunothread](#yunothread) 型のポインタを返し、失敗した場合には **NULL** を返します。

## start_yunothread

```c
yunothread_status start_yunothread (yunothread *thread);
```

この関数は作成されたスレッドを実行状態にします。
実行状態になっているスレッドにこの関数を再度使用した場合にどのような振る舞いをするかは未定義です。 
この関数は成功した場合には **YUNOTHREAD_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## wait_yunothread

```c
yunothread_status wait_yunothread (yunothread_wait_mode waitmode, yunothread *thread);
```

この関数は与えられたスレッドが終了するまで現在のスレッドを待機、あるいは対象のスレッドが終了しているかどうかを確認します。
この関数は第一引数に与えた定数によって振る舞いが変わります。
この関数が対応している定数の一覧はこちらになります。

| 定数 | 概要 | 
| ------------------- | ---- | 
| YUNOTHREAD_FOREVER | この定数が渡された場合、この関数は与えられたスレッドが終了するまで現在実行中のスレッドを待機状態にします。スレッドが終了あるいは中断した場合にはこの関数は **YUNOTHREAD_SUCCESS** を返します。何かしらの問題が発生した場合には **YUNOTHREAD_ERROR** が返されます。 | 
| YUNOTHREAD_NOWAIT  | この定数が渡された場合、この関数は与えられたスレッドの状態を確認し、それぞれに対応した値を返します。もしスレッドが終了していた場合にはこの関数は **YUNOTHREAD_SUCCESS** を返し、まだ実行中の場合には **YUNOTHREAD_BUSY** を返します。そして何かしらの問題が発生した場合には **YUNOTHREAD_ERROR** が返されます。 | 

## close_yunothread

```c
yunothread_status close_yunothread (yunothread *thread);
```

[make_yunothread_manually](#make_yunothread_manually) または [make_yunothread](#make_yunothread) で作成されたスレッドの資源を解放します。
この関数は成功した場合には **YUNOTHREAD_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## free_yunothread

```c
yunothread_status free_yunothread (yunothread *thread);
```

[make_yunothread](#make_yunothread) 関数で作成された [yunothread](#yunothread) の領域を解放します。
この関数は対象の [yunothread](#yunothread) が実行中・停止中に関わらず領域を解放しようとします。
きちんと後始末をしたい場合には [wait_yunothread](#wait_yunothread) 関数と [close_yunothread](#close_yunothread) 関数の実行後に呼出す必要があります。
この関数は成功した場合には **YUNOTHREAD_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。
