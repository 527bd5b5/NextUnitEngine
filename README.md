# Next Unit Engine

![スクリーンショット](./screenshot.png)

## これは何？

これは（仮説として）標準模型よりも小さい単一の物質「mono」と作用「effect」を独自で研究するために作成した、C++とOpenGLで動作する3Dシミュレーターです。

## 使用言語

C++ 26 (コンパイルはGNU Compiler Collection: GCC、フォーマットはClang-Formatを使用)

## 使用ライブラリー

- cmath
- freeglut (OpenGL Utility Toolkit: GLUT)

## 使用方法

makeでソースコードから実行ファイルを生成します。GCC以外のコンパイラーを使用する場合やライブラリーの専用パスを指定する場合は、Makefileを編集するか、個別にコマンドを実行します。

```sh:Bash
make
```

第1引数に世界の初期状態を記述したテキストファイル「NUE Unplayed Epilogue: NUE」のパスを指定して実行します。

```sh:Bash
./obj/NextUnitEngine world.nue
```

実行ファイルはNUEファイルを読み取り、monoやeffectを設定します。基本的な書式は以下の通りです。世界の変数については[CONFIG.md](./CONFIG.md)を、各テンプレートの変数については[TEMPLATE.md](./TEMPLATE.md)を参照してください。

```plaintext:world.nue
#<comment: something>

$<config_name: string>: <value: something>

@<template_name: string>
    origin: <x: double>, <y: double>, <z: double>
    force: <x: double>, <y: double>, <z: double>
    origin-noise: <double>
    force-noise: <double>
    <option_property: string>: <option_value: something>
    ...

@<template_name: string>
    ...
```

## オプション

`-s` `<sleep: int = 10>`<br />
フレームの待機時間（ミリ秒）を指定します。

`-f` `<fov: double = 60.0>`<br />
視野角を指定します。

`-fw` `<width: int = 640>`<br />
ウィンドウの横幅を指定します。

`-fh` `<height: int = 480>`<br />
ウィンドウの縦幅を指定します。

`-fx` `<pos_x: int = 10>`<br />
ウィンドウのX座標を指定します。

`-fy` `<pos_y: int = 10>`<br />
ウィンドウのY座標を指定します。

## 操作方法

キーボードやマウスで視界の移動や世界の操作が行えます。

`Q` `W` `E` `A` `S` `D`<br />
カメラを移動します。

`I` `J` `K` `L` もしくは `左ドラッグ`<br />
カメラを回転します。

`1` `2` `3` `4` `5` `6` `7` `8`<br />
カメラを定点に移動します。

`r`<br />
世界を初期状態に戻します。

`t`<br />
NUEファイルを読み込み直します。

`c`<br />
世界を一時停止・再生します。

`v`<br />
世界を1ステップだけ再生します。

`f`<br />
群を示す接続と重心の表示を切り替えます。

`g`<br />
軌道の表示を切り替えます。

`[`<br />
軌道を短くします。

`]`<br />
軌道を長くします。

`ESC`<br />
プログラムを終了します。
