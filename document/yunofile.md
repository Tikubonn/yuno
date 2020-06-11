
# File IO 

Yuno は同期・非同期双方のファイル入出力に対応しています。
Yuno によって開かれたファイルは同期・非同期問わず、すべて同じ手続きで操作することができます。

下記の例では、適当なファイルを開き、その内容を標準出力に書き出しています。

```c
#include <yuno.h>

static int write_to_file (void *sequence, yunosize size, yunofile *file){
  for (yunosize offset = 0; offset < readsize;){
    yunosize wrotesize;
    write_yunosize(sequence + offset, size - offset, output, &wrotesize);
    offset += wrotesize;
  }
  return 0;
}

#define BUFFER_SIZE 4096

int main (){
  yunofile *file = new_yunofile("example.txt", YUNOFILE_READABLE, 0);
  yunofile *output = new_yunostandard_output(0);
  while (1){
    char buffer[BUFFER_SIZE];
    yunosize readsize;
    read_yunofile(buffer, sizeof(buffer), file, &readsize);
    if (readsize == 0){
      break;
    }
    else {
      write_to_file(buffer, readsize, file);
    }
  }
  close_yunofile(file);
  close_yunofile(output);
  return 0;
}
```

## yunofile

Yuno によって開かれたファイルを管理する型です。

## open_yunofile, new_yunofile

```c
int open_yunofile (const char* filename, int flags, void *bufferseq, yunosize buffersize, yunofile *file);
yunofile *new_yunofile (const char* filename, int flags, yunosize buffersize);
```

引数 *filename* のファイルを作成あるいは開きます。

*open_yunofile* 関数も *new_yunofile* 関数もどちらともファイルを開きます。
*open_yunofile* 関数は開いたファイルを、引数 *file* に保存します。
*new_yunofile* 関数は開いたファイルを、動的に確保した領域に保存し、そのアドレスを返します。
*new_yunofile* 関数によって返されたファイルは、不要になった際に *free_yunofile* 関数で解放する必要があります。

引数 *flags* はこれらのフラグの論理和を受け取ります。
未定義のフラグあるいは無効な組み合わせを受け取った場合、
この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| フラグ | 概要 | 
| ---- | ---- | 
| YUNOFILE_READABLE | ファイルを読み込みモードで開きます。このフラグが単体で使用された場合、対象のファイルが存在しなければ、この関数は失敗し、*YUNODOES_NOT_EXISTS* エラーが設定されます。 | 
| YUNOFILE_WRITABLE | ファイルを書き込みモードで開きます。このフラグが含まれる場合、対象のファイルが存在しなければ、ファイルを新規に作成します。 | 
| YUNOFILE_TRUNCATE | このフラグはファイルを書き込みモードで開いた際、ファイルの内容を消去します。 | 
| YUNOFILE_APPEND   | このフラグはファイルを書き込みモードで開いた際、ファイルの書き込み位置を末尾に設定します。このフラグはファイルに追加のデータを書き込みたい場合に有用です。このフラグは *YUNOFILE_TRUNCATE* と一緒に指定することはできません。 | 
| YUNOFILE_SYNC     | ファイルを同期モードで開きます。*YUNOFILE_SYNC* および *YUNOFILE_ASYNC* が指定されない場合、この関数はファイルを同期モードで開きます。 | 
| YUNOFILE_ASYNC    | ファイルを非同期モードで開きます。このフラグは *YUNOFILE_SYNC* と一緒に指定することはできません。 | 

この関数によってファイルの内容が失われるか、
保持されるかは、引数 *flags* のフラグの組み合わせによって決まります。

| 例 | 概要 | 
| ---- | ---- | 
| YUNOFILE_WRITABLE                                           | ファイルが存在しているかに関係なく、ファイルを新規に作成します。古いファイルの内容は失われます。 | 
| YUNOFILE_WRITABLE \| YUNOFILE_APPEND                        | ファイルが存在していればそのファイルを開き、存在していない場合には新規に作成します。 | 
| YUNOFILE_WRITABLE \| YUNOFILE_READABLE                      | ファイルが存在していればそのファイルを開き、存在していない場合には新規に作成します。 | 
| YUNOFILE_WRITABLE \| YUNOFILE_READABLE \| YUNOFILE_TRUNCATE | ファイルが存在しているかに関係なく、ファイルを新規に作成します。古いファイルの内容は失われます。 | 

引数 *bufferseq* と *buffersize* は非同期操作時に使用される領域とそのサイズを受け取ります。
*new_yunofile* 関数は実行時に動的に領域を作成するため、引数に *bufferseq* を受け取りません。
もし非同期操作を行わない場合には、これらの値を `NULL` と０にすることができます。

ファイルを作成あるいは開くことに成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## open_yunostandard_input, open_yunostandard_output, open_yunostandard_error, new_yunostandard_input, new_yunostandard_output, new_yunostandard_error

```c
int open_yunostandard_input (int flags, void *bufferseq, yunosize buffersize, yunofile *file);
int open_yunostandard_output (int flags, void *bufferseq, yunosize buffersize, yunofile *file);
int open_yunostandard_error (int flags, void *bufferseq, yunosize buffersize, yunofile *file);
yunofile *new_yunostandard_input (int flags, yunosize buffersize);
yunofile *new_yunostandard_output (int flags, yunosize buffersize);
yunofile *new_yunostandard_error (int flags, yunosize buffersize);
```

これらの関数は標準入出力を開きます。

これらの関数はどちらとも標準入出力を開きます。
接頭辞に *open* が付く関数は、開いた標準入出力を引数 *file* に保存します。
接頭辞に *new* が付く関数は、開いた標準入出力を動的に確保した領域に保存し、そのアドレスを返します。

引数 *flags* はこれらのフラグの論理和を受け取ります。
未定義のフラグあるいは無効な組み合わせを受け取った場合、
この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| フラグ | 概要 | 
| ---- | ---- | 
| YUNOFILE_SYNC  | 標準入出力を同期モードで開きます。*flags* が０の場合、この関数はこのフラグを適用します。 | 
| YUNOFILE_ASYNC | ファイルを非同期モードで開きます。このフラグは *YUNOFILE_SYNC* と一緒に指定することはできません。 | 

引数 *bufferseq* と *buffersize* は非同期操作時に使用される領域とそのサイズを受け取ります。
接頭辞に *new* が付く関数は、実行時に動的に領域を作成するため、引数に *bufferseq* を受け取りません。
もし非同期操作を行わない場合には、これらの値を `NULL` と０にすることができます。

接頭辞に *open* が付く関数は、標準入出力を開くことに成功すると０を返します。
エラーが発生した場合、非ゼロの値を返します。
接頭辞に *new* が付く関数は、標準入出力を開くことに成功すると有効なアドレスを返します。
エラーが発生した場合、`NULL` を返します。

## write_yunofile 

```c
int write_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *wrotesizep);
```

引数 *sequence* のアドレスのデータを、ファイルに書き込みます。
この関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。
この関数を非同期モードで開かれたファイルに使用した場合、
この関数は書き込み操作が完了するまでの間、スレッドを待機させます。

引数 *sequence* と *size* は、それぞれ書き込むデータの先頭アドレスとその長さです。

引数 *file* は書き込み先のファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

データの書き込みに成功すると、この関数は書き込まれたデータの長さを、引数 *wrotesizep* に保存し、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## read_yunofile 

```c
int read_yunofile (void *sequence, yunosize size, yunofile *file, yunosize *readsizep);
```

ファイルの現在の位置から、引数 *size* 分のデータを読み込みます。
この関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。
この関数を非同期モードで開かれたファイルに使用した場合、
この関数は読み込み操作が完了するまでの間、スレッドを待機させます。

引数 *sequence* と *size* は、それぞれ読み込み先の領域とその大きさです。

引数 *file* は読み込み元のファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

データの読み込みに成功すると、この関数は読み込まれたデータの長さを、引数 *readsizep* に保存し、０を返します。
ファイル位置が終端に到達した場合や、読み込むデータがなくなってしまった場合、引数 *readsizep* は０になります。
エラーが発生した場合、この関数は非ゼロの値を返します。

## request_write_yunofile, wait_write_yunofile

```c
int request_write_yunofile (void *sequence, yunosize size, yunofile *file);
int wait_write_yunofile (yunowait_mode waitmode, yunofile *file, yunosize *wrotesizep);
```

ファイルに書き込み要求を行い、書き込み操作が完了するまで待機します。
これらの関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。

*request_write_yunofile* 関数は、引数 *sequence* のアドレスのデータをファイルに書き込むよう要求します。
この関数を実行した場合、必ず *wait_write_yunofile* 関数を実行し、ファイルへの書き込みを完了させなければなりません。

引数 *sequence* と *size* は、それぞれ書き込むデータの先頭アドレスとその長さです。

引数 *file* は書き込み先のファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイルへの書き込み要求が成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

--- 

*wait_write_yunofile* 関数は、指定された時間、要求された書き込み操作が完了するまで待機します。

引数 *waitmode* はこれらの定数のうちひとつを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| 定数 | 概要 |
| ---- | ---- |
| YUNOFOREVER | 書き込み操作が完了するまでの間、スレッドを待機させます。 | 
| YUNONOWAIT  | 書き込み操作が完了したか確認し、すぐさま結果を返します。YUNOFOREVER とは異なりスレッドを待機させません。 | 

引数 *file* は要求先のファイルです。
ファイルは *request_write_yunofile* 関数で、書き込み要求されていなければなりません。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイルへの書き込み操作が完了すると、この関数は書き込まれたデータの長さを、引数 *wrotesizep* に保存し、０を返します。
ファイルが書き込み中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。
エラーが発生した場合、この関数は非ゼロの値を返します。

## request_read_yunofile, wait_read_yunofile

```c
int request_read_yunofile (yunosize size, yunofile *file);
int wait_read_yunofile (void *sequence, yunowait_mode waitmode, yunofile *file, yunosize *readsizep);
```

ファイルに読み込み要求を行い、読み込み操作が完了するまで待機します。
これらの関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。

*request_read_yunofile* 関数は、引数 *size* 分のデータをファイルから読み込むよう要求します。
この関数を実行した場合、必ず *wait_read_yunofile* 関数を実行し、ファイルからの読み込みを完了させなければなりません。

引数 *file* は読み込み元のファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイルへの読み込み要求が成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

--- 

*wait_read_yunofile* 関数は、指定された時間、要求された読み込み操作が完了するまで待機します。

引数 *sequence* は読み込まれたデータを書き込む領域です。
この領域は *request_read_yunofile* 関数の実行時の引数 *size* 分の大きさが必要です。

引数 *waitmode* はこれらの定数のうちひとつを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| 定数 | 概要 |
| ---- | ---- |
| YUNOFOREVER | 読み込み操作が完了するまでの間、スレッドを待機させます。 | 
| YUNONOWAIT  | 読み込み操作が完了したか確認し、すぐさま結果を返します。YUNOFOREVER とは異なりスレッドを待機させません。 | 

引数 *file* は要求先のファイルです。
ファイルは *request_write_yunofile* 関数で、書き込み要求されていなければなりません。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイルへの読み込み操作が完了すると、この関数は読み込まれたデータの長さを、引数 *readsizep* に保存し、０を返します。
ファイルが読み込み中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。
エラーが発生した場合、この関数は非ゼロの値を返します。

## seek_yunofile 

```c
int seek_yunofile (yunossize distance, yunofile_whence whence, yunofile *file, yunosize *newoffsetp);
```

ファイル位置を変更します。
この関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。

引数 *distance* は相対的な位置を表す符号付き整数を受け取ります。

引数 *whence* は *distance* の基準となる位置です。
引数 *whence* はこれらの定数のうち、いずれかを受け取ります。
未定義の定数を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOFILE_BEGIN   | ファイル位置を先頭から *distance* の位置に設定します。 | 
| YUNOFILE_CURRENT | ファイル位置を現在位置から *distance* の位置に設定します。 | 
| YUNOFILE_END     | ファイル位置を終端位置から *distance* の位置に設定します。 | 

引数 *file* は位置を変更するファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイル位置の変更に成功すると、この関数は新しいファイル位置を *newoffsetp* に保存し、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## tell_yunofile 

```c
int tell_yunofile (yunofile *file, yunosize *offsetp);
```

現在のファイル位置を返します。
この関数は同期・非同期モードどちらで開かれたかに関係なく、使用することができます。

引数 *file* は位置を変更するファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイル位置の取得に成功すると、この関数は現在のファイル位置を *offsetp* に保存し、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## close_yunofile 

```c
int close_yunofile (yunofile *file);
```

開かれたファイルを閉じます。

引数 *file* は閉じる対象のファイルです。
ファイルが既に閉じられていた場合、この関数は失敗し、*YUNOALREADY_CLOSED* エラーが設定されます。
ファイルが別の非同期操作中の場合、この関数は失敗し、*YUNOBUSY* エラーが設定されます。

ファイルを閉じることに成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## yunofile_writablep

```c
bool yunofile_writablep (yunofile *file);
```

ファイルが書き込み用に開かれているか確認します。

この関数は必ず成功します。
引数 *file* が書き込み用に開かれていた場合、この関数は `true` を返します。
引数 *file* が書き込み用に開かれていなかった場合、この関数は `false` を返します。

## yunofile_readablep

```c
bool yunofile_readablep (yunofile *file);
```

ファイルが読み込み用に開かれているか確認します。

この関数は必ず成功します。
引数 *file* が読み込み用に開かれていた場合、この関数は `true` を返します。
引数 *file* が読み込み用に開かれていなかった場合、この関数は `false` を返します。

## yunofile_closedp

```c
bool yunofile_closedp (yunofile *file);
```

ファイルが既に閉じられているか確認します。

この関数は必ず成功します。
引数 *file* が閉じられていた場合、この関数は `true` を返します。
引数 *file* が閉じられていなかった場合、この関数は `false` を返します。

## yunofile_syncp

```c
bool yunofile_syncp (yunofile *file);
```

ファイルが同期モードで開かれているか確認します。

この関数は必ず成功します。
引数 *file* が同期モードで開かれていた場合、この関数は `true` を返します。
引数 *file* が同期モードで開かれていなかった場合、この関数は `false` を返します。

## yunofile_asyncp

```c
bool yunofile_asyncp (yunofile *file);
```

ファイルが非同期モードで開かれているか確認します。

この関数は必ず成功します。
引数 *file* が非同期モードで開かれていた場合、この関数は `true` を返します。
引数 *file* が非同期モードで開かれていなかった場合、この関数は `false` を返します。

## free_yunofile 

```c
int free_yunofile (yunofile *file);
```

*new_yunofile* 関数で確保されたメモリ領域を解放します。

メモリ領域の解放に成功した場合、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
