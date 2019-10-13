
# Pipe 

Yuno はパイプを使ったプロセス間通信にも対応しています。

Yuno のパイプは Unix のように書き込み用と読み込み用の端点を作成し、
プロセスごとに手動で不要な端点を閉じる方法で利用します。
下記の例ではパイプからの入力を標準出力に出力するサブプロセスを作成し、
そのプロセスにパイプ経由で簡単なメッセージを送信しています。

```c
#include <yuno.h>
#include <stdio.h>

typedef struct pipe {
  yunofile *input;
  yunofile *output;
} pipe;

static int __stdcall example (void *parameter){
  yunofile *pip = parameter;
  close_yunofile(pip->output);
  while (1){
    char buffer[1024];
    yunosize readsize;
    read_yunofile(pip->input, buffer, sizeof(buffer), &readsize);
    if (readsize == 0){
      break;
    }
    fwrite(buffer, 1, readsize, stdout);
  }
  return 0;
}

#define TEST_MESSAGE "this is a test message!\n"

int main (){
  yunofile *input;
  yunofile *output;
  make_yunopipe(0, 0, &input, &output);
  pipe pip;
  pip.input = input;
  pip.output = output;
  yunoprocess *process = make_yunoprocess(example, &pip);
  close_yunofile(pip.input);
  start_yunoprocess(process);
  write_yunofile(TEST_MESSAGE, sizeof(TEST_MESSAGE) -1, output);
  close_yunofile(pip.output);
  // >> this is a test message!\n
  wait_yunoprocess(YUNOPROCESS_FOREVER, process);
  close_yunoprocess(process);
  free_yunoprocess(process);
  return 0;
}
```

## make_yunopipe_manually

```c
yunopipe_status make_yunopipe_manually (
  void *inputbufferseq,
  yunosize inputbuffersize,
  void *outputbufferseq,
  yunosize outputbuffersize,
  yunofile *inputfile,
  yunofile *outputfile
);
```

この関数は新しくパイプを作成し、作成した読み込み用と書き込み用の端点をそれぞれ `inputfile` と `outputfile` に保存します。
引数 `inputbufferseq` と `inputbuffersize` はそれぞれ非同期読み込み用に使われる内部バッファのアドレスとその長さです。
もし非同期読み込みを行わないのであればそれぞれ **NULL** と **0** を与えてください。
引数 `outputbufferseq` と `outputbuffersize` はそれぞれ非同期書き込み用に使われる内部バッファのアドレスとその長さです。
もし非同期書き込みを行わないのであればそれぞれ **NULL** と **0** を与えてください。
作成に成功した場合にこの関数は **YUNOPIPE_SUCCESS** を返します。
失敗した場合にこの関数は **YUNOPIPE_ERROR** を返します。

## make_yunopipe

```c
yunopipe_status make_yunopipe (
  yunosize inputbuffersize,
  yunosize outputbuffersize,
  yunofile **inputfilep,
  yunofile **outputfilep
);
```

この関数は [make_yunopipe_manually](#make_yunopipe_manually) と同様にパイプを作成しますが、
保存用の [yunofile](README_FILEIO.md#yunofile) と内部バッファの領域を `malloc` で動的に確保する部分が異なります。
引数 `inputbuffersize` は非同期読み込み用に使われる内部バッファのサイズです。
もし非同期読み込みを行わないのであれば **0** を指定してください。
引数 `outputbuffersize` は非同期書き込み用に使われる内部バッファのサイズです。
もし非同期書き込みを行わないのであれば **0** を指定してください。
作成に成功した場合にこの関数は **YUNOPIPE_SUCCESS** を返します。
失敗した場合にこの関数は **YUNOPIPE_ERROR** を返します。

この関数によって動的に確保された領域は [free_yunofile](README_FILEIO.md#free_yunofile) 関数によって解放することができます。
