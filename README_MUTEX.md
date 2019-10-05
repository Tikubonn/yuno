
# Mutex

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

## make_yunomutex_manually

```c
yunomutex_status make_yunomutex_manually (yunomutex*);
```

## make_yunomutex

```c
yunomutex *make_yunomutex ();
```

## wait_yunomutex

```c
yunomutex_status wait_yunomutex (yunomutex*);
```

## release_yunomutex

```c
yunomutex_status release_yunomutex (yunomutex*);
```

## close_yunomutex

```c
yunomutex_status close_yunomutex (yunomutex*);
```

## free_yunomutex

```c
yunomutex_status free_yunomutex (yunomutex*);
```
