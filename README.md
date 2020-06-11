
# Yuno 

![](https://img.shields.io/badge/License-MIT-green)
![](https://img.shields.io/badge/Windows-OK-blue)
![](https://img.shields.io/badge/Linux-OK-blue)

Yuno は Windows/Linux が提供する機能を抽象化してくれるラッパーライブラリです。

このライブラリは「マルチプロセシング・マルチスレッディング・ファイルIO・排他制御」など多岐にわたる機能を提供します。
詳細は後述する [API Documentation](#api-documentation) をご参照ください。

このライブラリは、趣味で書いている自作処理系用に書かれたものです。
そのため、他ライブラリでは標準の機能が不足していたり、幾つかの機能に制限があります。

```c
#include <yuno.h>
#include <stdio.h>
#include <stdlib.h>

int globalint = 0;

static int entrypoint (void *parameter){
  globalint = 1;
  printf("globalint=%d\n", globalint); // globalint=1
  return 0;
}

int main (){
  yunoprocess *process = new_yunoprocess(entrypoint, NULL);
  start_yunoprocess(process);
  wait_yunoprocess(YUNOFOREVER, process);
  close_yunoprocess(process);
  printf("globalint=%d\n", globalint); // globalint=0
  return 0;
}
```

## API Documentation

- [Error](document/yunoerror.md)
- [Size](document/yunosize.md)
- [File IO](document/yunofile.md)
- [Multi Threading](document/yunothread.md)
- [Multi Processing](document/yunoprocess.md)
- [Mutex](document/yunomutex.md)
- [Semaphore](document/yunosemaphore.md)
- [Memory Allocation](document/yunomemory.md)
- [Shared Memory Allocation](document/yunoshared-memory.md)
- [Time](document/yunotime.md)

## Installation

Yuno は同梱されている makefile からビルドすることができます。

Linux 用にビルドしたい場合には、引数の `windows` を `linux` に書き換えて実行してください。
ビルドに成功すると、`dist` ディレクトリ以下に成果物が作成されます。

```shell 
make target=windows
```

## License 

Yuno は [MIT License](LICENSE) の許諾の下で公開されています。
