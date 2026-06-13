# Next Unit Engine - Template

## Ring

回転するリング状のmono群をX-Z平面上に設置します。

```plaintext
@ring
    # 全体の位置
    origin: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 全体の初速
    force: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 各monoの位置のばらつき
    origin-noise: <double = 0.0>

    # 各monoの初速のばらつき
    force-noise: <double = 0.0>

    # リングとして設置されるmonoの数
    mono-num: <int = 8>

    # リングの半径
    radius: <double = 0.125>

    # リングの回転速度、正の値で左回り
    velocity: <double = 0.00390625>
```

## Random

範囲内にmonoを無差別に設置します。

```plaintext
@random
    # 全体の位置
    origin: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 全体の初速
    force: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 各monoの位置のばらつき
    origin-noise: <double = 0.0>

    # 各monoの初速のばらつき
    force-noise: <double = 0.0>

    # 範囲内に設置されるmonoの数
    mono-num: <int = 256>

    # 範囲
    size: <x: double = 4.0>, <y: double = 4.0>, <z: double = 4.0>
```

## Grid

等間隔に並ぶ格子状のmono群を設置します。

```plaintext
@grid
    # 全体の位置
    origin: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 全体の初速
    force: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>

    # 各monoの位置のばらつき
    origin-noise: <double = 0.0>

    # 各monoの初速のばらつき
    force-noise: <double = 0.0>

    # 格子の数
    size: <x: int = 4>, <y: int = 4>, <z: int = 4>

    # 格子の大きさ
    scale: <double = 1.0>

    # 外面を固定
    fix-end: <boolean = false>
```
