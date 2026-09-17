# Next Unit Engine - Config

## Mono Graphic Scale

世界の描画規模を設定します。

```plaintext
$mono-graphic-scale: <double = 1.0>
```

## Mono Graphic Size

monoの視覚的な大きさを設定します。

```plaintext
$mono-graphic-size: <double = 0.01>
```

## Delta Times

effectの分割時間を設定します。値が小さいほどeffectが正確に計算されますが、状態の遷移が遅くなります。

```plaintext
$delta-times: <double = 6.103515625e-5>
```

## Cluster Threshold

2つ以上のmonoを群として判定する距離の閾値を設定します。

```plaintext
$cluster-threshold: <double = 0.3913165154385>
```

## Show Mono Index Label

monoの番地を描画します。

```plaintext
$show-mono-index-label: <boolean = false>
```

## Camera Position

スクリプト読み込み時にカメラの位置を設定します。

```plaintext
$camera-position: <x: double = 3.06186217848>, <y: double = 2.5>, <z: double = 3.06186217848>
```

## Camera Rotation

スクリプト読み込み時にカメラの角度を設定します。

```plaintext
$camera-rotation: <t: double = -30.0>, <p: double = 45.0>
```

## Camera Arc

スクリプト読み込み時に特定の座標（x, y, z）を任意の角度（t, p）と距離（r）で捉えるカメラを設定します。

```plaintext
$camera-arc: <x: double = 0.0>, <y: double = 0.0>, <z: double = 0.0>, <t: double = -30.0>, <p: double = 45.0>, <r: double = 5.0>
```
