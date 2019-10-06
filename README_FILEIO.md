
# File IO

Yuno は同期・非同期双方のファイル入出力をサポートしています。

下記の例ではひとつのファイルを開いてその内容を標準出力に出力しています。

```c
#include <yuno.h>

int main (){
  yunofile *file = open_yunofile("example.txt", YUNOFILE_READABLE, 0);
  yunofile *output = open_yunostandard_output(0);
  while (1){
    char buffer[1024];
    yunosize readsize;
    read_yunofile(buffer, sizeof(buffer), file, &readsize);
    if (readsize == 0){
      break;
    }
    for (yunosize woffset = 0; woffset < readsize;){
      yunosize wrotesize;
      write_yunosize(buffer + woffset, readsize - woffset, output, &wrotesize);
      woffset += wrotesize;
    }
  }
  close_yunofile(file);
  return 0;
}
```

## yunofile 

```c
typedef /* ... */ yunofile;
```

[yunofile](#yunofile) 型はファイルを表す型です。
この型はビルドされた環境によって定義が異なります。

## open_yunofile_manually

```c
yunofile_status open_yunofile_manually (
  const char *filename,
  int mode, 
  void *bufferseq,
  yunosize buffersize,
  yunofile *file
);
```

最初の引数で指定されたファイルを同期モードで開き、開いたファイルを最後の引数 `file` に保存します。
ファイルを開くことに成功した場合には、この関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

この関数は第２引数 `mode` に渡されたフラグによってどのようにファイルを開くのかを制御することができます。
Yuno が対応しているフラグの一覧は以下の通りになります。

| フラグ | 概要 | 
| ---- | ---- | 
| YUNOFILE_READABLE   | ファイルを読み込みモードで開きます。単体でこのフラグが指定された場合、対象のファイルが存在していなければこの関数は失敗し **YUNOFILE_DOES_NOT_EXISTS** を返します。 | 
| YUNOFILE_WRITABLE   | ファイルを書き込みモードで開きます。このフラグが指定された場合、対象のファイルが存在していなければファイルを新規に作成します。 | 
| YUNOFILE_TRUNCATE   | このフラグは **YUNOFILE_WRITABLE** と一緒に指定することができます。このフラグが指定された場合、対象のファイルを開く際にそのファイルの内容を消去します。 | 
| YUNOFILE_APPEND     | このフラグは **YUNOFILE_WRITABLE** と一緒に指定することができます。このフラグが指定された場合、対象のファイルを開いた際にファイルの書き込み位置を最後の位置に設定します。このフラグは **YUNO_TRUNCATE** と一緒に指定することはできません。 | 

第３引数 `bufferseq` と第４引数 `buffersize` はそれぞれ非同期IO用の関数で利用される、内部バッファとその長さです。
非同期IO用の関数で操作を行わないのであればそれぞれ **NULL** と **0** を与えてください。

## open_async_yunofile_manually

```c
yunofile_status open_async_yunofile_manually (
  const char *filename,
  int mode,
  void *bufferseq,
  yunosize buffersize,
  yunofile *file
);
```

最初の引数で指定されたファイルを非同期モードで開き、開いたファイルを最後の引数 file に保存します。
ファイルを開くことに成功した場合には、この関数は **YUNOFILE_SUCCESS** を返します。 
失敗した場合にはそれ以外の値を返します。
それ以外に関しては [open_yunofile_manually](#open_yunofile_manually) と同様です。

## open_yunofile 

```c
yunofile *open_yunofile (
  const char *filename, 
  int mode,
  yunosize buffersize
);
```

この関数は開いたファイルと内部のバッファの領域を `malloc` で動的に確保する以外は [open_yunofile_manually](#open_yunofile_manually) と同じ振る舞いをします。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## open_async_yunofile

```c
yunofile *open_async_yunofile (
  const char *filename, 
  int mode, 
  yunosize buffersize
);
```

この関数は開いたファイルと内部のバッファの領域を `malloc` で動的に確保する以外は [open_async_yunofile_manually](#open_async_yunofile_manually) と同じ振る舞いをします。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_input_manually

```c
yunofile *get_yunostandard_input_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準入力を開き第３引数に保存します。
標準入力を取得することに成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と 第２引数 `buffersize` はそれぞれ非同期用の関数で利用される内部バッファのアドレスとそのサイズです。
もし非同期の操作を行わないのであればこれらの値をそれぞれ **NULL** と **0** に設定してください。

## get_yunostandard_output_manually 

```c
yunofile *get_yunostandard_output_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準出力を開き第３引数に保存します。
標準出力を取得することに成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と 第２引数 `buffersize` はそれぞれ非同期用の関数で利用される内部バッファのアドレスとそのサイズです。
もし非同期の操作を行わないのであればこれらの値をそれぞれ **NULL** と **0** に設定してください。

## get_yunostandard_error_manually 

```c
yunofile *get_yunostandard_error_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準エラー出力を開き第３引数に保存します。
標準エラー出力を取得することに成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と 第２引数 `buffersize` はそれぞれ非同期用の関数で利用される内部バッファのアドレスとそのサイズです。
もし非同期の操作を行わないのであればこれらの値をそれぞれ **NULL** と **0** に設定してください。

## get_async_yunostandard_input_manually

```c
yunofile *get_async_yunostandard_input_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準入力を非同期モードで開く事を除いて [get_yunostandard_input_manually](#get_yunostandard_input_manually) と殆ど同じ振る舞いをします。
処理が無事に完了した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

## get_async_yunostandard_output_manually 

```c
yunofile *get_async_yunostandard_output_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準出力を非同期モードで開く事を除いて [get_yunostandard_input_manually](#get_yunostandard_input_manually) と殆ど同じ振る舞いをします。
処理が無事に完了した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

## get_async_yunostandard_error_manually 

```c
yunofile *get_async_yunostandard_error_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準エラー出力を非同期モードで開こうと試みることを除いて [get_yunostandard_input_manually](#get_yunostandard_input_manually) と殆ど同じ振る舞いをします。
処理が無事に完了した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。

## get_yunostandard_input 

```c
yunofile *get_yunostandard_input (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準入力を開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_output 

```c
yunofile *get_yunostandard_output (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準出力を開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_error 

```c
yunofile *get_yunostandard_error (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準エラー出力を開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_input 

```c
yunofile *get_async_yunostandard_input (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準入力を非同期モードで開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_output 

```c
yunofile *get_async_yunostandard_output (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準出力を非同期モードで開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_error 

```c
yunofile *get_async_yunostandard_error (yunosize buffersize);
```

[open_yunofile](#open_yunofile) のように標準エラー出力を非同期モードで開き [yunofile](#yunofile) と内部バッファの領域を動的に確保します。
ファイルを開くことに成功した場合にはこの関数は動的に確保された [yunofile](#yunofile) のアドレスを返します。
失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## write_yunofile

```c
yunofile_status write_yunofile (
  void *sequence,
  yunosize size,
  yunofile *file, 
  yunosize *wrotesizep
);
```

この関数は引数 `sequence` が示すアドレスのデータを `size` の長さ分ファイルに書き込みます。
ファイルが非同期モードで開かれていた場合にはファイルの書き込みが終わるまでの間まで実行しているスレッドを待機させます。
ファイルへの書き込みが成功した場合にこの関数は **YUNOFILE_SUCCESS** を返し、書き込まれたデータの長さを `wrotesizep` に保存します。
この関数が失敗した場合にはそれ以外の値を返します。

## request_write_yunofile

```c
yunofile_status request_write_yunofile (
  void *sequence,
  yunosize size,
  yunofile *file
);
```

## wait_write_yunofile

```c
yunofile_status wait_write_yunofile (
  yunofile *file,
  yunosize *wrotesizep
);
```

## read_yunofile

```c
yunofile_status read_yunofile (
  void sequence*,
  yunosize size,
  yunofile *file,
  yunosize *readsizep
);
```

この関数はファイルの現在位置から `size` の長さ分のデータを `sequence` に読み込みます。
ファイルが非同期モードで開かれていた場合にはファイルの読み込みが終わるまでの間まで実行しているスレッドを待機させます。
ファイルからの読み込みが成功した場合にこの関数は **YUNOFILE_SUCCESS** を返し、読み込まれたデータの長さを `readsizep` に保存します。
ファイルがすでに終端に達していた場合には読み込まれたデータの長さは **0** になります。
この関数が失敗した場合にはそれ以外の値を返します。

## request_read_yunofile

```c
yunofile_status request_read_yunofile (
  yunosize size,
  yunofile *file
);
```

## wait_read_yunofile

```c
yunofile_status wait_read_yunofile (
  void *sequence,
  yunofile *file, 
  yunosize *readsizep
);
```

## seek_yunofile

```c
yunofile_status seek_yunofile (
  yunosize offset,
  yunofile_whence whence,
  yunofile *file,
  yunosize *newoffsetp
);
```

この関数はファイルの位置を `whence` の位置を基準に `offset` に変更します。
ファイル位置の変更に成功した場合にこの関数は**YUNOFILE_SUCCESS** を返し、引数 `newoffsetp` に新しい位置を保存します。
失敗した場合にはこの関数は **YUNOFILE_ERROR** を返します。

引数 `whence` には以下の値を使用することができます。

| 基点 | 概要 | 
| ---- | ---- |
| YUNOFILE_BEGIN   | ファイルの先頭を基点に位置を設定します。 | 
| YUNOFILE_CURRENT | ファイルの現在位置を基点に位置を設定します。 | 
| YUNOFILE_END     | ファイルの終端位置を基点に位置を設定します。 | 

もし仮にファイルが非同期モードで開かれており、
何かしらの処理が行われている最中であった場合には、
この関数は即座に処理を中断し **YUNOFILE_BUSY** を返します。

## tell_yunofile

```c
yunofile_status tell_yunofile (
  yunofile *file,
  yunosize *offsetp
);
```

この関数は現在のファイルの位置を `offsetp` に保存します。
ファイル位置の変更に成功した場合にこの関数は**YUNOFILE_SUCCESS** を返し、引数 `offsetp` に新しい位置を保存します。
失敗した場合にはこの関数は **YUNOFILE_ERROR** を返します。
もし仮にファイルが非同期モードで開かれており、
何かしらの処理が行われている最中であった場合には、
この関数は即座に処理を中断し **YUNOFILE_BUSY** を返します。

## close_yunofile

```c
yunofile_status close_yunofile (yunofile *file);
```

このファイルは開かれているファイルを閉じます。
ファイルを閉じることに成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合には **YUNOFILE_ERROR** を返します。
ファイルが非同期で開かれており何かしらの操作が行われている最中であれば
この関数は即座に処理を中断し **YUNOFILE_BUSY** を返します。

## free_yunofile

```c
yunofile_status free_yunofile (yunofile*);
```

下記に示すこれらの関数によって確保された yunofile の領域を解放します。
領域の解放に成功した場合にはこの関数は **YUNOFILE_SUCCESS** を返します。
失敗した場合にはこの関数はそれ以外の値を返します。

* [open_yunofile](#open_yunofile) 
* [open_async_yunofile](#open_async_yunofile) 
* [get_yunostandard_input](#get_yunostandard_input)
* [get_yunostandard_output](#get_yunostandard_output)
* [get_yunostandard_error](#get_yunostandard_error)
* [get_async_yunostandard_input](#get_async_yunostandard_input)
* [get_async_yunostandard_output](#get_async_yunostandard_output)
* [get_async_yunostandard_error](#get_async_yunostandard_error)
* [make_yunopipe](README_PIPE.md#make_yunopipe) 

この関数はたとえ非同期モードで開かれたファイルが何かしらの操作を実行中であったとしても関係なく領域を解放しようとするのでご注意ください。
