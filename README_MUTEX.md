
# Mutex

Yuno はミューテックスを用いた排他制御に対応しています。

ミューテックスを利用することで複数の処理を並行処理する際にそれぞれのタスク間で同期をとることができます。
これによって、特定の処理の不可分性を保証したり、同時に同じメモリにアクセスしてしまうことを防ぐことができます。

下記の例では複数のスレッドを作成し、
それぞれのスレッドで同期をとりながらグローバル変数 countup をインクリメントしています。

```c
#include <yuno.h>
#include <stdio.h>

static int countup;

static int example (void *parameter){
  yunomutex *mutex = parameter;
  wait_yunomutex(YUNOMUTEX_FOREVER, mutex);
  countup++;
  release_yunomutex(mutex);
  return 0;
}

#define YUNOTHREAD_COUNT 3

int main (){
  countup = 0;
  yunomutex *mutex = make_yunomutex();
  yunothread *threads[YUNOTHREAD_COUNT];
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    threads[index] = make_yunothread(example, mutex);
  }
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    start_yunothread(threads[index]);
  }
  for (size_t index = 0; index < YUNOTHREAD_COUNT; index++){
    wait_yunothread(YUNOTHREAD_FOREVER, threads[index]);
    close_yunothread(threads[index]);
    free_yunothread(threads[index]);
  }
  printf("countup = %d\n", countup);
  // >> countup = 3
  free_yunomutex(mutex);
  return 0;
}
```

## yunomutex

```c
typedef /* ... */ yunomutex;
```

この型は Yuno で作成されたミューテックスを表す型です。
この型は環境によって定義が異なります。

## make_yunomutex_manually

```c
yunomutex_status make_yunomutex_manually (yunomutex *mutex);
```

この関数は新しいミューテックスを作成します。
この関数で作成されたミューテックスはサブプロセスでも有効に動作します。
関数が成功した場合には **YUNOMUTEX_SUCCESS** を返し、
引数に作成されたミューテックスを保存します。
失敗した場合には **YUNOMUTEX_ERROR** を返します。

## make_yunomutex

```c
yunomutex *make_yunomutex ();
```

この関数は [make_yunomutex_manually](#make_yunomutex_manually) と同様にミューテックスを作成しますが、
保存先の領域を動的に確保する部分が異なります。
関数が成功した場合には動的に確保された [yunomutex](#yunomutex) のアドレスが返ります。
失敗した場合には **NULL** が返ります。

この関数で動的に確保された領域は [free_yunomutex](#free_yunomutex) 関数で解放することができます。

## wait_yunomutex

```c
yunomutex_status wait_yunomutex (
  yunomutex_wait_mode waitmode,
  yunomutex *mutex
);
```

この関数は与えられたミューテックスの使用権が得られるまでの間、現在のスレッドを待機状態にします。
誰かが保持していた使用権が放棄されると即座にこの関数はミューテックスの使用権を獲得します。
この関数で獲得した使用権は任意の処理後に release_yunomutex 関数を使って解放してください。

この関数は第１引数 `waitmode` に与えた定数によって振る舞いが変わります。
この関数が対応している定数の一覧はこちらになります。

| 定数 | 概要 | 
| ---- | ---- | 
| YUNOMUTEX_FOREVER | 引数 `mutex` の使用権が得られるまでの間、現在のスレッドを待機状態にします。`mutex` の使用権を無事得られた場合にこの関数は **YUNOMUTEX_SUCCESS** を返します。失敗した場合にこの関数は **YUNOMUTEX_ERROR** を返します。 | 
| YUNOMUTEX_NOWAIT  | この定数が与えられた場合、この関数は即座に引数 `mutex` の使用権を得ようとします。もし `mutex` が誰にも独占されていない場合には使用権を獲得しこの関数は **YUNOMUTEX_SUCCESS** を返します。`mutex` が何者かに独占されていた場合にこの関数は **YUNOMUTEX_BUSY** を返します。失敗した場合には関数は **YUNOMUTEX_ERROR** を返します。

<!--
| YUNOMUTEX_FOREVER | 引数 `mutex` が未使用状態になるまで現在のスレッドを待機状態にします。引数 `mutex` が無事に未使用状態になった場合にこの関数は **YUNOMUTEX_SUCCESS** を返します。失敗した場合にこの関数は **YUNOMUTEX_ERROR** を返します。 | 
| YUNOMUTEX_NOWAIT  | 引数 `mutex` が未使用状態であるかどうかを確認し、即座に状態に応じた値を返します。スレッドの待機は行いません。引数 `mutex` が未使用状態の場合にこの関数は **YUNOMUTEX_SUCCESS** を返します。引数 `mutex` が使用状態の場合には **YUNOMUTEX_BUSY** を返します。失敗した場合にこの関数は **YUNOMUTEX_ERROR** を返します。 | 
-->

## release_yunomutex

```c
yunomutex_status release_yunomutex (yunomutex *mutex);
```

この関数は [wait_yunomutex](#wait_yunomutex) 関数で使用中の状態になったミューテックスを未使用状態に戻します。
この関数が成功した場合には **YUNOMUTEX_SUCCESS** を返します。
失敗した場合には **YUNOMUTEX_ERROR** を返します。

## close_yunomutex

```c
yunomutex_status close_yunomutex (yunomutex *mutex);
```

[make_yunomutex_manually](#make_yunomutex_manually) または [make_yunomutex](#make_yunomutex) で作成されたミューテックスの資源を解放します。
この関数は成功した場合には **YUNOTMUTEX_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。

## free_yunomutex

```c
yunomutex_status free_yunomutex (yunomutex *mutex);
```

[make_yunomutex](#make_yunomutex) 関数で作成された [yunomutex](#yunomutex) の領域を解放します。
この関数は対象の [yunomutex](#yunomutex) が実行中・停止中に関わらず領域を解放しようとします。
きちんと後始末をしたい場合には [wait_yunomutex](#wait_yunomutex) 関数と [close_yunomutex](#close_yunomutex) 関数の実行後に呼出す必要があります。
この関数は成功した場合には **YUNOMUTEX_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。
