
# Semaphore

```c
```

## make_yunosemaphore_manually

```c
yunosemaphore_status make_yunosemaphore_manually (yunosemaphore*);
```

## make_named_yunosemaphore_manually

```c
yunosemaphore_status make_named_yunosemaphore_manually (const char*, yunosemaphore*);
```

## make_yunosemaphore

```c
yunosemaphore *make_yunosemaphore ();
```

## make_named_yunosemaphore

```c
yunosemaphore *make_named_yunosemaphore (const char*);
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
