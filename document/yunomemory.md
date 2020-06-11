
# Memory Allocation 

Yuno はメモリ領域を動的に確保する手段を提供しています。

## allocate_yunomemory 

```c
void *allocate_yunomemory (yunosize size);
```

読み書き可能なメモリ領域を動的に確保します。

引数 *size* は確保する領域のサイズです。
この値は必ず０よりも大きくなくてはなりません。
もし引数 *size* が０以下の値を受け取った場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。

メモリ領域の確保に成功すると、この関数は確保した領域の先頭アドレスを返します。
十分なメモリ領域が確保できなかった場合、この関数は失敗し、*YUNONOT_ENOUGH_MEMOTY* エラーを設定します。
エラーが発生した場合、この関数は `NULL` を返します。

## free_yunomemory 

```c
int free_yunomemory (void *address, yunosize size);
```

確保されたメモリ領域を解放します。

この関数は *allocate_yunomemory* 関数で確保されたメモリ領域を解放します。

引数 *address* は *allocate_yunomemory* 関数で返されたアドレスです。
引数 *address* が *allocate_yunomemory* 関数で返されたアドレスでない場合、この関数は失敗し、*YUNOARGUMENT_ERROR* エラーを設定します。
引数 *address* が既に解放済みの領域を指していた場合、動作は未定義です。

引数 *size* は *allocate_yunomemory* 関数で要求したメモリ領域のサイズです。
この値が *allocate_yunomemory* 関数で要求したメモリ領域のサイズと異なる場合、動作は未定義です。

確保されたメモリ領域の解放に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は `NULL` を返します。
