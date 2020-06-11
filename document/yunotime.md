
# Time 

Yuno は指定された時間スレッドを停止させる *yunosleep* 関数、
現在の UNIX 時間を取得する *yunotime* 関数を提供しています。

```c
#include <yuno.h>
#include <stdio.h>

int main (){
  yunoseconds firsttime;
  yunotime(&firsttime);
  yunoseconds(3, 0);
  yunoseconds secondtime;
  yunotime(&secondtime);
  printf("firsttime=%d secondtime=%d\n", firsttime, secondtime);
  return 0;
}
```

## yunotime 

```c
int yunotime (yunoseconds *secondsp);
```

現在の UNIX 時間を取得します。

時刻の取得に成功すると、この関数は現在の UNIX 時間を引数 *secondsp* に保存し、０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。

## yunosleep

```c
int yunosleep (yunoseconds seconds, yunoseconds milliseconds);
```

指定された時間、スレッドの動作を停止します。

引数 *seconds* は停止させる秒数を受け取ります。

引数 *milliseconds* は停止させるミリ秒単位の秒数を受け取ります。

スレッドの停止に成功すると、この関数は０を返します。
エラーが発生した場合、この関数は非ゼロの値を返します。
