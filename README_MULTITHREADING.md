
# MultiThreading 

Yuno はマルチスレッディングにも対応しています。  
マルチスレッディングはマルチプロセシングのように並行で処理を実行しますが、メモリを共有している部分が異なります。
そのため、複数のスレッドで同時に同じデータを書き換えたりした場合には、データを破壊してしまう可能性があります。
それらを回避したい場合には [yunomutex](README_MUTEX.md) や [yunosemaphore](README_SEMAPHORE.md) など Yuno が提供している排他制御の機構を検討することをお勧めします。

```c
#include <yuno.h>
#include <stdio.h>

static int global_number;

static int example (void *parameter){
  global_number = 1;
  printf("global_number in subthread = %d\n", global_number);
  // >> global_number in subthread = 1
  return 0;
}

int main (){
  global_number = 0;
  yunothread *thread = make_yunothread(example, NULL);
  start_yunothread(thread);
  wait_yunothread(thread);
  close_yunothread(thread);
  free_yunothread(thread);
  printf("global_number in main thread = %d\n", global_number);
  // >> global_number in main thread = 1
  return 0;
}
```

## make_yunothread_manually

```c
yunothread_status make_yunothread_manually (yunothread_entry_point entrypoint, void *parameter, yunothread *threado);
```

## make_yunothread

```c
yunothread *make_yunothread (yunothread_entry_point entrypoint, void *parameter);
```

## start_yunothread

```c
yunothread_status start_yunothread (yunothread *thread);
```

## wait_yunothread

```c
yunothread_status wait_yunothread (yunothread_wait_mode waitmode, yunothread *thread);
```

## close_yunothread

```c
yunothread_status close_yunothread (yunothread *thread);
```

## free_yunothread

```c
yunothread_status free_yunothread (yunothread *thread);
```
