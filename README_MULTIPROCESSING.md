
# MultiProcessing 

Yuno はマルチプロセシングに対応しています。

Yuno のマルチプロセシングの関数は Linux の fork のように、
現在実行しているプロセスを複製し、それぞれが並行に処理を実行します。
子プロセスは親プロセスのメモリを複製しただけの別プロセスなので、双方のメモリ上にあるデータを書き換えたとしても、互いに影響を与えることはありません。

プロセス間での通信を行いたい場合には Yuno が提供している [Pipe](README_PIPE.md) や [Shared Memory](README_SHARED_MEMORY.md) の機能を使用することを検討してもいいかもしれません。
Windows では fork のような概念はありませんが、Yuno はライブラリ側で工夫することによって似たような機能を再現しています。
詳細はライブラリのソースコードを直接読んでください。

```c
#include <yuno.h>
#include <stdio.h>

static int global_number;

static int example (void *parameter){
  global_number = 1;
  printf("global_number in subprocess = %d\n", global_number);
  // >> global_number in subprocess = 1
  return 0;
}

int main (){
  global_number = 0;
  yunoprocess *process = make_yunoprocess(example, NULL);
  start_yunoprocess(process);
  wait_yunoprocess(process);
  close_yunoprocess(process);
  free_yunoprocess(process);
  printf("global_number in main process = %d\n", global_number);
  // >> global_number in main process = 0
  return 0;
}
```

## yunoprocess

```c
// typedef yunoprocess;
```

yunoprocess 型は Yuno で作成されたサブプロセスを表す型です。
これはビルドされた環境によって定義が異なります。

## yunoprocess_entry_point 

```c
typedef int __stdcall (*yunoprocess_entry_point)(void*);
```

yunoprocess_entry_point 型は Yuno で作成されるサブプロセス上で実行される関数の型です。
この型が要求する返り値がサブプロセスの終了コードになります。

## make_yunoprocess_manually

```c
yunoprocess_status make_yunoprocess_manually (yunoprocess_entry_point entrypoint, void *parameter, yunoprocess *process);
```

複製先のプロセスで実行する関数とその引数を受け取り新規にサブプロセスを作成します。  
作成されたプロセスは第三引数に保存されます。
作成されたサブプロセスは作成後すぐには実行されず、[start_yunoprocess](#start_yunoprocess) 関数が実行されるまで停止した状態になります。
プロセス自体は作成されているので、作成後は [close_yunoprocess](#close_yunoprocess) 関数で資源を解放してください。
この関数は成功すると **YUNOPROCESS_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## make_yunoprocess

```c
yunoprocess *make_yunoprocess (yunoprocess_entry_point entrypoint, void *parameter);
```

この関数は [make_yunoprocess_manually](#make_yunoprocess_manually) と同様に新規にサブプロセスを作成しますが、
作成されたサブプロセスを `malloc` で確保された領域に保存し、その領域を返り値として返します。
この関数によって作成された [yunoprocess](#yunoprocess) ポインタは不要になった場合に [free_yunoprocess](#free_yunoprocess) 関数で解放する必要があります。
この関数は成功した場合には新規の有効な [yunoprocess](#yunoprocess) 型のポインタを返し、失敗した場合には **NULL** を返します。

## start_yunoprocess

```c
yunoprocess_status start_yunoprocess (yunoprocess *process);
```

この関数は作成されたプロセスを実行状態にします。  
実行状態になっているプロセスにこの関数を再度使用した場合にどのような振る舞いをするかは未定義です。
この関数は成功した場合には **YUNOPROCESS_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## wait_yunoprocess

```c
yunoprocess_status wait_yunoprocess (yunoprocess_wait_mode waitmode, yunoprocess *process);
```

この関数は与えられたプロセスが終了するまで現在のスレッドを待機、あるいは対象のプロセスが終了しているかどうかを確認します。
この関数は第一引数に与えた定数によって振る舞いが変わります。
この関数が対応している定数の一覧はこちらになります。

| 定数 | 概要 | 
| ------------------- | ---- | 
| YUNOPROCESS_FOREVER | この定数が渡された場合、この関数は与えられたプロセスが終了するまで現在実行中のスレッドを待機状態にします。プロセスが終了あるいは中断した場合にはこの関数は **YUNOPROCESS_SUCCESS** を返します。何かしらの問題が発生した場合には **YUNOPROCESS_ERROR** が返されます。 | 
| YUNOPROCESS_NOWAIT  | この定数が渡された場合、この関数は与えられたプロセスの状態を確認し、それぞれに対応した値を返します。もしプロセスが終了していた場合にはこの関数は **YUNOPROCESS_SUCCESS** を返し、まだ実行中の場合には **YUNOPROCESS_BUSY** を返します。そして何かしらの問題が発生した場合には **YUNOPROCESS_ERROR** が返されます。 | 

## close_yunoprocess

```c
yunoprocess_status close_yunoprocess (yunoprocess *process);
```

[make_yunoprocess_manually](#make_yunoprocess_manually) または [make_yunoprocess](#make_yunoprocess) で作成されたプロセスの資源を解放します。  
この関数は成功した場合には **YUNOPROCESS_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## free_yunoprocess 

```c
yunoprocess_status free_yunoprocess (yunoprocess *process);
```

[make_yunoprocess](#make_yunoprocess) 関数で作成された [yunoprocess](#yunoprocess) の領域を解放します。  
この関数は対象の [yunoprocess](#yunoprocess) が実行中・停止中に関わらず領域を解放しようとします。
きちんと後始末をしたい場合には [wait_yunoprocess](#wait_yunoprocess) 関数と [close_yunoprocess](#close_yunoprocess) 関数の実行後に呼出す必要があるでしょう。
この関数は成功した場合には **YUNOPROCESS_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。
