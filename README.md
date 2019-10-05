
# Yuno 

![](https://img.shields.io/badge/License-MIT-green)
![](https://img.shields.io/badge/Windows-OK-blue)
![](https://img.shields.io/badge/Linux-OK-blue)
![](https://img.shields.io/badge/Mac-X-red)

Yuno は Windows/Linux でマルチプロセシング・マルチスレッディング・ファイルIOなどの OS 間での差異を抽象化してくれるライブラリです。
Windows でも fork のようにプロセスを複製して並行処理できたり、
同期・非同期どちらで開かれたファイルでも、同じ手続きで操作できたり、
自分の欲しい機能がいっぱい詰まってます。

このライブラリは自分用に書いたものを善意で公開しているだけなので、致命的ではない限り不具合などは修正するつもりはないです。
なので問題に出くわしたら自分で解決してください。


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

## Documentation

Yuno が提供している機能の紹介をしています。

* [File IO](README_FILEIO.md)
* [MultiProcessing](README_MULTIPROCESSING.md)
* [Pipe](README_PIPE.md)
* [MultiThreading](README_MULTITHREADING.md)
* [Mutex](README_MUTEX.md)
* [Semaphore](README_SEMAPHORE.md)
* [Shared Memory](README_SHARED_MEMORY.md)
* [Time](README_TIME.md)

## Installation

Yuno は makefile が同梱されているので下記のコマンドからビルドすることができます。
ビルドが成功するとディレクトリ `dist` 以下に `yuno.lib` `yuno.dll` `yuno.h` の三つの成果物が作成されます。

```shell
$ make target=windows
```

また Yuno は簡単な動作確認用のテストコードも同梱しているので下記のコマンドからビルド・実行することができます。

```shell
$ make test target=windows
```

## TODO

* 現在のバージョンではビルドに素の makefile を使用していますが、将来的には autoconf かそれに準ずるビルド方式を採用する予定です。
* ごく稀に発現する Windows でのマルチプロセシングでの奇妙な振る舞い(おそらくメモリのコピーの失敗によるものと推定)の解決方法を解明し修正可能であれば修正したいです。
  ただしこのライブラリを趣味で使う分にはあまり問題にはならないので優先度はかなり低いです。
* マルチプロセスで共有メモリを利用した場合に、稀にプロセスの制御がおかしくなる不具合があるので、原因を見つけ次第解決したいです。

## License 

Yuno は [MIT License](LICENSE) の許諾の下で公開されています。
