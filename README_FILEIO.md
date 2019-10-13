
# File IO

Yuno は「同期・非同期」双方のファイル入出力をサポートしています。

下記の例では適当なファイルを開き、その内容を標準出力に出力しています。

```c
#include <yuno.h>

int main (){
  yunofile *file = open_yunofile("example.txt", YUNOFILE_READABLE, 0);
  yunofile *output = get_yunostandard_output(0);
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

yunofile 型はファイルを表す型です。
この型は各環境によって定義が異なります。

## yunofile_status 

```c
typedef enum yunofile_status {
  YUNOFILE_SUCCESS,
  YUNOFILE_ERROR,
  YUNOFILE_BUSY
} yunofile_status;
```

yunofile_status 型は 
[yunofile](#yunofile) に関連する関数の実行結果を表す列挙型です。

それぞれの定数が意味する関数の実行結果は以下の通りです。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFILE_SUCCESS | 関数が成功した。 | 
| YUNOFILE_ERROR   | 関数で何かしらの問題が発生した。 | 
| YUNOFILE_BUSY    | 操作対象の [yunofile](#yunofile) が既に別の非同期操作を実行中だった。この定数が返されたならば、[wait_read_yunofile](#wait_read_yunofile) 等の待ち受け関数で操作の完了を待つ必要があります。 | 

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
ファイルを開くことに成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
処理が失敗した場合には **YUNOFILE_ERROR** を返します。

この関数は第２引数 `mode` に渡されたフラグの組み合わせによって、どのようにファイルを開くのかを制御することができます。
この関数が対応しているフラグの一覧は以下の通りになります。

| フラグ | 概要 | 
| ---- | ---- | 
| YUNOFILE_READABLE   | ファイルを読み込みモードで開きます。単体でこのフラグが指定された場合、対象のファイルが存在していなければこの関数は失敗し **YUNOFILE_DOES_NOT_EXISTS** を返します。 | 
| YUNOFILE_WRITABLE   | ファイルを書き込みモードで開きます。このフラグが指定された場合、対象のファイルが存在していなければファイルを新規に作成します。 | 
| YUNOFILE_TRUNCATE   | このフラグは **YUNOFILE_WRITABLE** と一緒に指定することができます。このフラグが指定された場合、対象のファイルが既に存在していた場合にファイルの末端位置を 0 に設定します。 | 
| YUNOFILE_APPEND     | このフラグは **YUNOFILE_WRITABLE** と一緒に指定することができます。このフラグが指定された場合、対象のファイルが既に存在していた場合にファイルの書き込み位置を最後の位置に設定します。このフラグは **YUNO_TRUNCATE** と一緒に指定することはできません。 | 

第３引数 `bufferseq` と第４引数 `buffersize` はそれぞれ非同期IO用の内部バッファとその長さです。
非同期IO用の関数で操作を行わないのであればそれぞれ **NULL** と **0** を与えることができます。

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

最初の引数で指定されたファイルを非同期モードで開き、開いたファイルを最後の引数 `file` に保存します。
ファイルを開くことに成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。 
そして処理が失敗した場合には **YUNOFILE_ERROR** の値を返します。
それ以外の振る舞いは [open_yunofile_manually](#open_yunofile_manually) とほとんど同じです。

## open_yunofile 

```c
yunofile *open_yunofile (
  const char *filename, 
  int mode,
  yunosize buffersize
);
```

この関数は開いたファイルの保存先の領域と、内部バッファの領域を動的に確保する以外は [open_yunofile_manually](#open_yunofile_manually) と同じ振る舞いをします。
ファイルを開くことに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## open_async_yunofile

```c
yunofile *open_async_yunofile (
  const char *filename, 
  int mode, 
  yunosize buffersize
);
```

この関数は開いたファイルの保存先の領域と、内部バッファの領域を動的に確保する以外は [open_async_yunofile_manually](#open_async_yunofile_manually) と同じ振る舞いをします。
ファイルを開くことに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_input_manually

```c
yunofile *get_yunostandard_input_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は OS から標準入力を取得し、最後の引数 `file` に保存します。
標準入力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と第２引数 `buffersize` はそれぞれ非同期IO用の内部バッファとその長さです。
非同期IO用の関数で操作を行わないのであればそれぞれ **NULL** と **0** を与えることができます。

## get_yunostandard_output_manually 

```c
yunofile *get_yunostandard_output_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は OS から標準出力を取得し、最後の引数 `file` に保存します。
標準出力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と第２引数 `buffersize` はそれぞれ非同期IO用の内部バッファとその長さです。
非同期IO用の関数で操作を行わないのであればそれぞれ **NULL** と **0** を与えることができます。

## get_yunostandard_error_manually 

```c
yunofile *get_yunostandard_error_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は OS から標準エラー出力を取得し、最後の引数 `file` に保存します。
標準エラー出力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

第１引数 `bufferseq` と第２引数 `buffersize` はそれぞれ非同期IO用の内部バッファとその長さです。
非同期IO用の関数で操作を行わないのであればそれぞれ **NULL** と **0** を与えることができます。

## get_async_yunostandard_input_manually

```c
yunofile *get_async_yunostandard_input_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準入力を非同期モードで取得することを除き [get_yunostandard_input_manually](#get_yunostandard_input_manually) とほとんど同じ振る舞いをします。
標準入力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

## get_async_yunostandard_output_manually 

```c
yunofile *get_async_yunostandard_output_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準出力を非同期モードで取得することを除き [get_yunostandard_output_manually](#get_yunostandard_output_manually) とほとんど同じ振る舞いをします。
標準出力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

## get_async_yunostandard_error_manually 

```c
yunofile *get_async_yunostandard_error_manually (
  void *bufferseq, 
  yunosize buffersize,
  yunofile *file
);
```

この関数は標準エラー出力を非同期モードで取得することを除き [get_yunostandard_error_manually](#get_yunostandard_error_manually) とほとんど同じ振る舞いをします。
標準エラー出力の取得に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
そして処理が失敗した場合には **YUNOFILE_ERROR** を返します。

## get_yunostandard_input 

```c
yunofile *get_yunostandard_input (yunosize buffersize);
```

この関数は取得した標準入力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_yunostandard_input_manually](#open_yunostandard_input_manually) と同じ振る舞いをします。
標準入力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_output 

```c
yunofile *get_yunostandard_output (yunosize buffersize);
```

この関数は取得した標準出力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_yunostandard_output_manually](#open_yunostandard_output_manually) と同じ振る舞いをします。
標準出力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_yunostandard_error 

```c
yunofile *get_yunostandard_error (yunosize buffersize);
```

この関数は取得した標準エラー出力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_yunostandard_error_manually](#open_yunostandard_error_manually) と同じ振る舞いをします。
標準エラー出力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_input 

```c
yunofile *get_async_yunostandard_input (yunosize buffersize);
```

この関数は取得した標準入力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_async_yunostandard_input_manually](#open_async_yunostandard_input_manually) と同じ振る舞いをします。
標準入力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_output 

```c
yunofile *get_async_yunostandard_output (yunosize buffersize);
```

この関数は取得した標準出力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_async_yunostandard_output_manually](#open_async_yunostandard_output_manually) と同じ振る舞いをします。
標準出力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
この関数によって動的に確保された領域は [free_yunofile](#free_yunofile) 関数を実行することで解放することができます。

## get_async_yunostandard_error 

```c
yunofile *get_async_yunostandard_error (yunosize buffersize);
```

この関数は取得した標準エラー出力の保存先の領域と、内部バッファの領域を動的に確保する以外は [open_async_yunostandard_error_manually](#open_async_yunostandard_error_manually) と同じ振る舞いをします。
標準エラー出力を取得することに成功した場合、この関数は動的に確保された [yunofile](#yunofile) 型のアドレスを返します。
そして処理が失敗した場合にはこの関数は **NULL** を返します。
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
ファイルが非同期モードで開かれていた場合、ファイルの書き込みが終わるまでの間、実行しているスレッドを待機させます。
ファイルへの書き込みが成功した場合、この関数は **YUNOFILE_SUCCESS** を返し、書き込まれたデータの長さを `wrotesizep` に保存します。
既にファイルが別の書き込み操作中の場合には **YUNOFILE_BUSY** を返します。
もし処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

## request_write_yunofile

```c
yunofile_status request_write_yunofile (
  void *sequence,
  yunosize size,
  yunofile *file
);
```

この関数は引数 `sequence` のデータを `size` の長さ分、非同期でファイルに書き込みます。
ファイルへの書き込み要求が成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
既にファイルが別の書き込み操作中の場合には **YUNOFILE_BUSY** を返します。
もし処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

もし書き込み先のファイルが同期モードで開かれていた場合には、
この関数は通常通り同期モードで書き込みを行います。
同期・非同期に関係なくこの関数でファイルへの書き込み要求を行った場合には、
必ず [wait_write_yunofile](#wait_write_yunofile) 関数で書き込みの完了を受け取ってください。

## wait_write_yunofile

```c
yunofile_status wait_write_yunofile (
  yunofile_wait_mode waitmode,
  yunofile *file,
  yunosize *wrotesizep
);
```

この関数は [request_write_yunofile](#request_write_yunofile) 関数で要求された非同期の書き込みが完了するまでの間、現在のスレッドを待機させます。

この関数は第１引数 `waitmode` によって以下のように振る舞いが変わります。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFILE_FOREVER | この定数が渡された場合、この関数は非同期の書き込みが完了するまでの間、現在のスレッドを停止します。そして書き込みが完了した場合、この関数は **YUNOFILE_SUCCESS** を返し、最後の引数 `wrotesizep` に書き込まれたデータの長さを保存します。そして処理が失敗した場合にこの関数は **YUNOFILE_ERROR** を返します。 | 
| YUNOFILE_NOWAIT  | この定数が渡された場合、この関数は非同期の書き込みが完了しているかどうかを確認し、その状態に応じた返り値を返します。 もし書き込みが完了していた場合、この関数は **YUNOFILE_SUCCESS** を返し、最後の引数 `wrotesizep` に書き込まれたデータの長さを保存します。まだ書き込みが完了していない場合には **YUNOFILE_BUSY** を返します。そして処理が失敗した場合にこの関数は **YUNOFILE_ERROR** を返します。 | 

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
ファイルが非同期モードで開かれていた場合にはファイルの読み込みが終わるまでの間、実行しているスレッドを待機させます。
ファイルからの読み込みが成功した場合、この関数は **YUNOFILE_SUCCESS** を返し、読み込まれたデータの長さを `readsizep` に保存します。
もう既にファイルが終端に達していた場合、読み込まれたデータの長さは **0** になります。
既にファイルが別の読み込み操作中である場合、この関数は **YUNOFILE_BUSY** を返します。
もし処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

## request_read_yunofile

```c
yunofile_status request_read_yunofile (
  yunosize size,
  yunofile *file
);
```

この関数は引数 `size` の長さ分のデータを非同期でファイルから読み込みます。
ファイルへの読み込み要求が成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
ファイルが既に別の読み込み操作中である場合にこの関数は **YUNOFILE_BUSY** を返します。
処理が失敗した場合にこの関数は **YUNOFILE_ERROR** を返します。

もし読み込み元のファイルが同期モードで開かれていた場合には、
この関数は通常通り同期モードで読み込みを行います。
同期・非同期に関係なくこの関数でファイルへの読み込み要求を行った場合には、
必ず [wait_read_yunofile](#wait_read_yunofile) 関数で読み込みの完了を受け取ってください。

## wait_read_yunofile

```c
yunofile_status wait_read_yunofile (
  void *sequence,
  yunofile_wait_mode waitmode,
  yunofile *file, 
  yunosize *readsizep
);
```

この関数は [request_read_yunofile](#request_read_yunofile) 関数で要求された非同期の読み込みが完了するまでの間、現在のスレッドを待機させます。

この関数は第１引数 `waitmode` によって下記のように振る舞いが変わります。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFILE_FOREVER | この定数が渡された場合にこの関数は非同期の読み込みが完了するまでの間、現在のスレッドを停止します。読み込みが完了した場合にこの関数は **YUNOFILE_SUCCESS** を返し、最後の引数 `readsizep` に読み込まれたデータの長さを保存します。もし処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。 | 
| YUNOFILE_NOWAIT  | この定数が渡された場合にこの関数は非同期の読み込みが完了しているかどうかを確認し、状態に応じた返り値を返します。 もし読み込みが完了していた場合にこの関数は **YUNOFILE_SUCCESS** を返し、 最後の引数 `readsizep` に読み込まれたデータの長さを保存します。まだ読み込みが完了していない場合にこの関数は **YUNOFILE_BUSY** を返します。もし処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。 | 

## seek_yunofile

```c
yunofile_status seek_yunofile (
  yunosize offset,
  yunofile_whence whence,
  yunofile *file,
  yunosize *newoffsetp
);
```

この関数はファイルの位置を引数 `whence` を基準に引数 `offset` の位置に変更します。
ファイル位置の変更に成功した場合、この関数は**YUNOFILE_SUCCESS** を返し、引数 `newoffsetp` に新しい位置を保存します。
もしファイルが非同期操作の最中であった場合、この関数は **YUNOFILE_BUSY** を返します。
処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

引数 `whence` には以下の値を使用することができます。

| 基点 | 概要 | 
| ---- | ---- |
| YUNOFILE_BEGIN   | ファイルの先頭を基点に位置を設定します。 | 
| YUNOFILE_CURRENT | ファイルの現在位置を基点に位置を設定します。 | 
| YUNOFILE_END     | ファイルの終端位置を基点に位置を設定します。 | 

## tell_yunofile

```c
yunofile_status tell_yunofile (
  yunofile *file,
  yunosize *offsetp
);
```

この関数は現在のファイルの位置を `offsetp` に保存します。
ファイル位置の取得に成功した場合、この関数は**YUNOFILE_SUCCESS** を返し、引数 `offsetp` に新しい位置を保存します。
もしファイルが非同期操作の最中であった場合、この関数は **YUNOFILE_BUSY** を返します。
処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

## close_yunofile

```c
yunofile_status close_yunofile (yunofile *file);
```

このファイルは開かれているファイルを閉じます。
ファイルを閉じることに成功した場合にこの関数は **YUNOFILE_SUCCESS** を返します。
もしファイルが非同期操作の最中であった場合、この関数は **YUNOFILE_BUSY** を返します。
処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

## free_yunofile

```c
yunofile_status free_yunofile (yunofile*);
```

下記に示すこれらの関数によって確保された yunofile の領域を解放します。
領域の解放に成功した場合、この関数は **YUNOFILE_SUCCESS** を返します。
処理が失敗した場合、この関数は **YUNOFILE_ERROR** を返します。

* [open_yunofile](#open_yunofile) 
* [open_async_yunofile](#open_async_yunofile) 
* [get_yunostandard_input](#get_yunostandard_input)
* [get_yunostandard_output](#get_yunostandard_output)
* [get_yunostandard_error](#get_yunostandard_error)
* [get_async_yunostandard_input](#get_async_yunostandard_input)
* [get_async_yunostandard_output](#get_async_yunostandard_output)
* [get_async_yunostandard_error](#get_async_yunostandard_error)
* [make_yunopipe](README_PIPE.md#make_yunopipe) 
