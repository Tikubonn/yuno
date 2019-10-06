
# Semaphore

```c
#include <yuno.h>

static int __yunocall example (void *parameter){
  yunosemaphore *semaphore = parameter;
  wait_yunosemaphore(YUNOSEMAPHORE_FOREVER, semaphore);
  yunosleep(1);
  release_yunosemaphore(semaphore);
  return 0;
}

#define PROCESS_COUNT 12

int main (){
  yunosemaphore *semaphore = make_yunosemaphore(3);
  yunoprocess *processes[PROCESS_COUNT];
  for (size_t index = 0; index < PROCESS_COUNT; index++){
    processes[index] = make_yunoprocess(example, semaphore);
  }
  for (size_t index = 0; index < PROCESS_COUNT; index++){
    start_yunoprocess(processes[index]);
  }
  for (size_t index = 0; index < PROCESS_COUNT; index++){
    wait_yunoprocess(YUNOPROCESS_FOREVER, processes[index]);
    close_yunoprocess(processes[index]);
    free_yunoprocess(processes[index]);
  }
  free_yunosemaphore(semaphore);
  return 0;
}
```

## make_yunosemaphore_manually

```c
yunosemaphore_status make_yunosemaphore_manually (int, yunosemaphore*);
```

## make_yunosemaphore

```c
yunosemaphore *make_yunosemaphore (int);
```

## wait_yunosemaphore

```c
yunosemaphore_status wait_yunosemaphore (yunosemaphore*);
```

## release_yunosemaphore

```c
yunosemaphore_status release_yunosemaphore (yunosemaphore*);
```

## close_yunosemaphore

```c
yunosemaphore_status close_yunosemaphore (yunosemaphore*);
```

## free_yunosemaphore

```c
yunosemaphore_status free_yunosemaphore (yunosemaphore*);
```
