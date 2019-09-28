
# Time

現在時刻の取得や `yunosleep` などのプロセスを一時停止させる関数などを紹介します。

```c
int main (){
  yunosleep(1);
  return 0;
}
```

## yunosleep

```c
yunosleep_status yunosleep (int);
```

この関数は指示された秒数の間、現在実行しているプロセスを停止させます。
この関数は成功すると **YUNOSLEEP_SUCCESS** を返します。
失敗した場合にはそれ以外の値を返します。
