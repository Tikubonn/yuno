
# File IO

Yuno は同期・非同期双方のファイル入出力をサポートしています。  
下記の例ではひとつのファイルを開いてその内容を標準出力に出力しています。

```c
#include <yuno.h>

int main (){
  yunofile *file = open_yunofile("example.txt", YUNOFILE_READABLE, 0);
  yunofile *output = open_yunostandard_output(0);
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

## open_yunofile_manually

```c
yunofile_status open_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
```

## open_async_yunofile_manually

```c
yunofile_status open_async_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
```

## open_yunofile 

```c
yunofile *open_yunofile (const char*, int, yunosize);
```

## open_async_yunofile

```c
yunofile *open_async_yunofile (const char*, int, yunosize);
```

## open_yunostandard_input_manually

```c
yunofile *open_yunostandard_input_manually (yunosize);
```

## open_yunostandard_output_manually 

```c
yunofile *open_yunostandard_output_manually (yunosize);
```

## open_yunostandard_error_manually 

```c
yunofile *open_yunostandard_error_manually (yunosize);
```

## open_async_yunostandard_input_manually

```c
yunofile *open_async_yunostandard_input_manually (yunosize);
```

## open_async_yunostandard_output_manually 

```c
yunofile *open_async_yunostandard_output_manually (yunosize);
```

## open_async_yunostandard_error_manually 

```c
yunofile *open_async_yunostandard_error_manually (yunosize);
```

## open_yunostandard_input 

```c
yunofile *open_yunostandard_input (yunosize);
```

## open_yunostandard_output 

```c
yunofile *open_yunostandard_output (yunosize);
```

## open_yunostandard_error 

```c
yunofile *open_yunostandard_error (yunosize);
```

## open_async_yunostandard_input 

```c
yunofile *open_async_yunostandard_input (yunosize);
```

## open_async_yunostandard_output 

```c
yunofile *open_async_yunostandard_output (yunosize);
```

## open_async_yunostandard_error 

```c
yunofile *open_async_yunostandard_error (yunosize);
```

## write_yunofile

```c
yunofile_status write_yunofile (void*, yunosize, yunofile*, yunosize*);
```

## request_write_yunofile

```c
yunofile_status request_write_yunofile (void*, yunosize, yunofile*);
```

## wait_write_yunofile

```c
yunofile_status wait_write_yunofile (yunofile*, yunosize*);
```

## read_yunofile

```c
yunofile_status read_yunofile (void*, yunosize, yunofile*, yunosize*);
```

## request_read_yunofile

```c
yunofile_status request_read_yunofile (yunosize, yunofile*);
```

## wait_read_yunofile

```c
yunofile_status wait_read_yunofile (void*, yunofile*, yunosize*);
```

## seek_yunofile

```c
yunofile_status seek_yunofile (yunosize, yunofile*, yunosize*);
```

## tell_yunofile

```c
yunofile_status tell_yunofile (yunofile*, yunosize*);
```

## close_yunofile

```c
yunofile_status close_yunofile (yunofile*);
```

## free_yunofile

```c
yunofile_status free_yunofile (yunofile*);
```
