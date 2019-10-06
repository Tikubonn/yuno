
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
  void *inputfilebufferseq,
  yunosize inputfilebuffersize,
  void *outputfilebufferseq,
  yunosize outputfilebuffersize,
  yunofile *inputfile,
  yunofile *outputfile
);
```

## make_yunopipe

```c
yunopipe_status make_yunopipe (
  yunosize inputfilebuffersize,
  yunosize outputfilebuffersize,
  yunofile **inputfilep,
  yunofile **outputfilep
);
```
