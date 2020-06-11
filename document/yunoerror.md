
# Error 

Yuno は発生したエラーを取得できる機能を提供しています。

## yunoerror 

エラーの種類を表す列挙型です。

この型はこれらの値を取ります。

| エラー | 概要 | 
| ---- | ---- | 
| YUNONOERROR           | エラーは発生しなかった。 | 
| YUNOBUSY              | オブジェクトが使用中である。 | 
| YUNOARGUMENT_ERROR    | 関数が無効な引数を受け取った。 | 
| YUNOALREADY_CLOSED    | オブジェクトは既に閉じられている。 | 
| YUNODOES_NOT_EXIST    | 存在しないファイルを開こうとした。 |
| YUNOIS_A_DIRECTORY    | ディレクトリを開こうとした。 | 
| YUNOPERMISSION_ERROR  | 関数は権限により失敗した。 | 
| YUNOOS_ERROR          | OS 側で何かしらのエラーが発生した。 | 
| YUNONOT_ENOUGH_MEMORY | 関数がメモリ不足で失敗した。 | 
| YUNOERROR             | 上記で分類できないエラーが発生した。 | 

## get_yunoerror

```c
yunoerror get_yunoerror ();
```

Yuno で発生したエラーの種類を返します。

この関数は Yuno が提供する関数で発生したエラーの種類を返します。
この関数の返す値は Yuno が提供する関数を実行するたびに変化します。
この関数はスレッドセーフです。

この関数は必ず成功します。
