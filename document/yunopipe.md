
# Pipe 

Yuno はプロセス間通信のためのパイプにも対応しています。

Yuno のパイプは UNIX のように書き込み用と読み込み用の端点を作成します。

下記の例では、パイプからの入力を標準出力に出力するプロセスを作成し、
そのプロセスにパイプ経由でデータを送信しています。

```c
#include <yuno.h>
#include <stdbool.h>

typedef struct process_argument {
  yunofile *input;
  yunofile *output;
} process_argument;

static int write_to_file (void *sequence, yunosize size, yunofile *file){
  for (yunosize offset = 0; offset < size;){
    yunosize wrotesize;
    if (write_yunofile(sequence + offset, size - offset, file, &wrotesize) != 0){
      return 1;
    }
    offset += wrotesize;
  }
  return 0;
}

#define BUFFER_SIZE 1024

static int entrypoint (void *parameter){
  process_argument *pargument = parameter;
  yunofile *output = new_yunostandard_output(0, 0);
  close_yunofile(pargument->output);
  while (true){
    char buffer[BUFFER_SIZE];
    yunosize readsize;
    read_yunofile(buffer, sizeof(buffer), pargument->input, &readsize);
    if (0 < readsize){
      write_to_file(buffer, readsize, output);
    }
    else {
      break;
    }
  }
  close_yunofile(pargument->input);
  close_yunofile(output);
  return 0;
}

#define TEST_DATA "this is a test data.\n"

int main (){
  yunofile *input;
  yunofile *output;
  new_yunopipe(0, 0, 0, &input, &output);
  process_argument pargument;
  pargument.input = input;
  pargument.output = output;
  yunoprocess *process = new_yunoprocess(entrypoint, &pargument);
  start_yunoprocess(process);
  write_to_file(TEST_DATA, sizeof(TEST_DATA) -1, output);
  close_yunoprocess(input);
  close_yunoprocess(output);
  wait_yunoprocess(YUNOFOREVER, process);
  close_yunoprocess(process);
  return 0;
}
```

## make_yunopipe, new_yunopipe 

```c
int make_yunopipe(int flags, void *inputbufferseq, yunosize inputbuffersize, , void *outputbufferseq, yunosize outputbuffersize, yunofile *inputfilep, yunofile *outputfilep);
int new_yunopipe(int flags, yunosize inputbuffersize, yunosize outputbuffersize, yunofile *inputfilep, yunofile *outputfilep);
```

プロセス間通信のためのパイプを作成します。

*make_yunopipe* 関数も *new_yunopipe* 関数もどちらともパイプを作成します。
*make_yunopipe* 関数は開いた作成したパイプを、引数 *inputfilep* と引数 *outputfilep* に保存します。
*new_yunopipe* 関数は開いたファイルを、動的に確保した領域に保存し、そのアドレスを引数 *inputfilep* と引数 *outputfilep* に保存します。
*new_yunopipe* 関数によって返されたファイルは、不要になった際に *free_yunofile* 関数で解放する必要があります。

引数 *flags* はこれらのフラグの論理和を受け取ります。
未定義のフラグあるいは無効な組み合わせを受け取った場合、
この関数は失敗し、*YUNOARGUMENT_ERROR* エラーが設定されます。

| フラグ | 概要 | 
| ---- | ---- | 
| YUNOFILE_SYNC  | 標準入出力を同期モードで開きます。*flags* が０の場合、この関数はこのフラグを適用します。 | 
| YUNOFILE_ASYNC | ファイルを非同期モードで開きます。このフラグは *YUNOFILE_SYNC* と一緒に指定することはできません。 | 

接尾辞に *bufferseq* と *buffersize* が付く引数は、非同期操作時に使用される領域とそのサイズを受け取ります。
接頭辞に *new* が付く関数は、実行時に動的に領域を作成するため、接尾辞に *bufferseq* が付く引数を要求しません。
もし非同期操作を行わない場合には、これらの値を `NULL` と０にすることができます。

パイプの作成に成功した場合、これらの関数は０を返します。
エラーが発生した場合、これらの関数は非ゼロの値を返します。
