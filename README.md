
# Yuno 

![](https://img.shields.io/badge/License-MIT-green)
![](https://img.shields.io/badge/Windows-OK-blue)
![](https://img.shields.io/badge/Linux-OK-blue)

Yuno は Windows/Linux が提供する機能を同じ手続きで利用できるよう抽象化してくれるライブラリです。
このライブラリは「マルチプロセシング・マルチスレッディング・ファイルIO」など多岐に渡る機能を提供します。
詳細は後述する [API Documentation](#api-documentation) をご参照ください。

下記のコードは簡単な使用例です。
コードを簡潔にするためにあえて例外時の処理は省いています。
このコードはサブプロセスを作成し、各プロセス内の広域変数を書き換えます。
Yuno の作成するサブプロセスは親プロセスのメモリ領域を複製するため、
それぞれのメモリが書き換えられたとしても互いの振る舞いに影響を与えることはありません。

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

## API Documentation

こちらでは Yuno が提供している機能の紹介を紹介しています。

* [File IO](README_FILEIO.md)
* [MultiProcessing](README_MULTIPROCESSING.md)
* [Pipe](README_PIPE.md)
* [MultiThreading](README_MULTITHREADING.md)
* [Mutex](README_MUTEX.md)
* [Semaphore](README_SEMAPHORE.md)
* [Shared Memory](README_SHARED_MEMORY.md)
* [Time](README_TIME.md)

## Installation

Yuno は makefile が同梱されており、下記のコマンドからビルドすることができます。
ビルドが成功するとディレクトリ `dist` 以下に「ヘッダファイル・静的ライブラリ・動的リンクライブラリ」の三つの成果物が作成されます。
Linux 用にビルドしたい場合には下記のコマンドの `windows` を `linux` に置き換えてください。

```shell
$ make target=windows
```

また Yuno は簡単な動作確認用のテストコードも同梱されており、下記のコマンドからビルド・実行することができます。

```shell
$ make test target=windows
```

## TODO

* ごく稀に発現する Windows でのマルチプロセシングでの奇妙な振る舞い(おそらくメモリのコピーの失敗によるものと推定)の解決方法を解明し修正可能であれば修正したいです。
  ただしこのライブラリを趣味で使う分にはあまり問題にはならないので優先度はかなり低いです。
* Windows で共有メモリの機能を利用した際に、稀にマルチプロセスの制御がおかしくなる不具合を確認しています。
  こちらも原因を見つけ次第解決したいです。

## License 

Yuno は [MIT License](LICENSE) の許諾の下で公開されています。
