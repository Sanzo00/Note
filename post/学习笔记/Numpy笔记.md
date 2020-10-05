[b站视频](https://www.bilibili.com/video/BV1Ex411L7oT)

[numpy.ipynb](https://github.com/Sanzona/files/blob/master/ipynb/numpy%E7%AC%94%E8%AE%B0.ipynb)

## numpy属性


```python
import numpy as np

array = np.array([[1,2,3],[2,3,4]])
print(array)
# 维度
print('number of dimenson:', array.ndim)

# 形状
print('shape:', array.shape)

# 元素个数
print('size:', array.size)
```

    [[1 2 3]
     [2 3 4]]
    number of dimenson: 2
    shape: (2, 3)
    size: 6


## 创建数组


```python
# 指定数据类型
a = np.array([1, 2, 3], dtype=np.float)
print(a.dtype)
print(a)
```

    float64
    [1. 2. 3.]



```python
# 全0矩阵
a = np.zeros((3, 4), dtype=np.int)
print(a)
```

    [[0 0 0 0]
     [0 0 0 0]
     [0 0 0 0]]



```python
# 全1矩阵
a = np.ones((3, 4))
print(a)
```

    [[1. 1. 1. 1.]
     [1. 1. 1. 1.]
     [1. 1. 1. 1.]]



```python
# 未初始化的矩阵
a = np.empty((3, 4))
print(a)
```

    [[1. 1. 1. 1.]
     [1. 1. 1. 1.]
     [1. 1. 1. 1.]]



```python
# 指定元素范围，[10， 20) 步长为2
a = np.arange(10, 20, 2)
print(a)
```

    [10 12 14 16 18]



```python
# 指定矩阵形状
a = np.arange(10).reshape((5, 2))
print(a)
```

    [[0 1]
     [2 3]
     [4 5]
     [6 7]
     [8 9]]



```python
# 等差数列，[1,10]分成3份
a = np.linspace(1, 10, 6).reshape((2, 3))
print(a)
```

    [[ 1.   2.8  4.6]
     [ 6.4  8.2 10. ]]


## 基础运算


```python
# 数组的加减乘除
a = np.array([10, 20, 30, 40])
b = np.array([1, 2, 3, 4])
print('a:', a)
print('b:', b)

c = a + b
print('a+b:', c)

c = a - b
print('a-b:', c)

c = a * b
print('a*b:', c)

c = a / b
print('a/b:', c)

c = a**2
print('a^3:', c)
```

    a: [10 20 30 40]
    b: [1 2 3 4]
    a+b: [11 22 33 44]
    a-b: [ 9 18 27 36]
    a*b: [ 10  40  90 160]
    a/b: [10. 10. 10. 10.]
    a^3: [ 100  400  900 1600]



```python
# 三角函数
a = np.array([30, 45, 60, 90]) # 默认弧度制
pi = np.arcsin(1)*2
print(np.pi)

a = np.multiply(a, pi/180)

print('a:', a)

c = np.sin(a)
print(c)

c = np.cos(a)
print(c)

c = np.tan(a)
print(c)
```

    3.141592653589793
    a: [0.52359878 0.78539816 1.04719755 1.57079633]
    [0.5        0.70710678 0.8660254  1.        ]
    [8.66025404e-01 7.07106781e-01 5.00000000e-01 6.12323400e-17]
    [5.77350269e-01 1.00000000e+00 1.73205081e+00 1.63312394e+16]



```python
# 随机生成矩阵
a = np.random.random((2, 4))
print(a)
print('min:', np.min(a))
print('max:', np.max(a))
print('sum:', np.sum(a))

# 1: 行 0: 列
print('min in each col:', np.min(a, axis=0))
print('min in each row:', np.min(a, axis=1))
```

    [[0.33028884 0.20715399 0.67513249 0.7976253 ]
     [0.09172116 0.65765596 0.04538128 0.36034413]]
    min: 0.045381281632210335
    max: 0.7976253001665536
    sum: 3.165303150763041
    min in each col: [0.09172116 0.20715399 0.04538128 0.36034413]
    min in each row: [0.20715399 0.04538128]



```python
# 数值运算
a = np.arange(1, 13).reshape(3, 4)
print(a)

# 最小值索引
print(np.argmin(a))

# 最大值索引
print(np.argmax(a))
```

    [[ 1  2  3  4]
     [ 5  6  7  8]
     [ 9 10 11 12]]
    0
    11



```python
# 平均值
print(np.average(a))
print(np.mean(a))
print(a.mean())
```

    6.5
    6.5
    6.5



```python
# 中位数
print(np.median(a))
```

    6.5



```python
# 前缀和
print(np.cumsum(a))
```

    [ 1  3  6 10 15 21 28 36 45 55 66 78]



```python
# 一阶差
print(np.diff(a))
```

    [[1 1 1]
     [1 1 1]
     [1 1 1]]



```python
# 非零的坐标
print(np.nonzero(a))
```

    (array([0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2], dtype=int64), array([0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3], dtype=int64))



```python
# 逐行排序
a = np.arange(14, 2, -1).reshape(3,4)
print(np.sort(a))
```

    [[11 12 13 14]
     [ 7  8  9 10]
     [ 3  4  5  6]]



```python
# clip
print(a)
print(np.clip(a, 5, 10))
```

    [[14 13 12 11]
     [10  9  8  7]
     [ 6  5  4  3]]
    [[10 10 10 10]
     [10  9  8  7]
     [ 6  5  5  5]]


## 矩阵运算


```python
# 矩阵相乘
a = np.array([[1,0], [1,2]])
b = np.arange(4).reshape(2,2)
print(a)
print(b)

c = np.dot(a, b)
# c = a.dot(b)
print(c)
```

    [[1 0]
     [1 2]]
    [[0 1]
     [2 3]]
    [[0 1]
     [4 7]]



```python
# 矩阵转置
print(a)
print(np.transpose(a))
print(a.T)
```

    [[1 0]
     [1 2]]
    [[1 1]
     [0 2]]
    [[1 1]
     [0 2]]


## 索引


```python
a = np.arange(1, 13).reshape(3, 4)
print(a)

# 第1行
print(a[1])
print(a[1, :])
```

    [[ 1  2  3  4]
     [ 5  6  7  8]
     [ 9 10 11 12]]
    [5 6 7 8]
    [5 6 7 8]



```python
# 第1列
print(a[:,1])
```

    [ 2  6 10]



```python
# 第1行的[1,3)
print(a[1, 1:3])
```

    [6 7]



```python
# 第（2，3）
print(a[2][3])
print(a[2, 3])
```

    12
    12



```python
# 迭代行
for row in a:
    print(row)
```

    [1 2 3 4]
    [5 6 7 8]
    [ 9 10 11 12]



```python
# 迭代列
for row in a.T:
    print(row)
```

    [1 5 9]
    [ 2  6 10]
    [ 3  7 11]
    [ 4  8 12]



```python
# 迭代每一个元素
print(a.flatten())

for item in a.flat:
    print(item)
```

    [ 1  2  3  4  5  6  7  8  9 10 11 12]
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11
    12


## array合并


```python
A = np.array([1, 1, 1])
B = np.array([2, 2, 2])

# 垂直合并
C = np.vstack((A, B))
print(C)

# 水平合并
D = np.hstack((A, B))
print(D)
```

    [[1 1 1]
     [2 2 2]]
    [1 1 1 2 2 2]



```python
# 数组转为行向量
print(A)
A = A[np.newaxis, :]
print(A)
```

    [1 1 1]
    [[1 1 1]]



```python
# 数组转为列向量
print(B)
B = B[:, np.newaxis]
print(B)
```

    [2 2 2]
    [[2]
     [2]
     [2]]



```python
# concatenate合并
A = np.array([1, 1, 1])[:, np.newaxis]
B = np.array([2, 2, 2])[:, np.newaxis]
print(A)
print(B)

# 垂直合并
C = np.concatenate((A,B,B,A), axis=0)

# 水平合并
D = np.concatenate((A,B,B,A), axis=1)
print(C)
print(D)
```

    [[1]
     [1]
     [1]]
    [[2]
     [2]
     [2]]
    [[1]
     [1]
     [1]
     [2]
     [2]
     [2]
     [2]
     [2]
     [2]
     [1]
     [1]
     [1]]
    [[1 2 2 1]
     [1 2 2 1]
     [1 2 2 1]]


## array分割


```python
# 等量分割
A = np.arange(12).reshape((3, 4))
print(A)

# 上下分割成3份
print(np.split(A, 3, axis=0))
print(np.vsplit(A, 3))

# 左右分割2份
print(np.split(A, 2, axis=1))
print(np.hsplit(A, 2))
```

    [[ 0  1  2  3]
     [ 4  5  6  7]
     [ 8  9 10 11]]
    [array([[0, 1, 2, 3]]), array([[4, 5, 6, 7]]), array([[ 8,  9, 10, 11]])]
    [array([[0, 1, 2, 3]]), array([[4, 5, 6, 7]]), array([[ 8,  9, 10, 11]])]
    [array([[0, 1],
           [4, 5],
           [8, 9]]), array([[ 2,  3],
           [ 6,  7],
           [10, 11]])]
    [array([[0, 1],
           [4, 5],
           [8, 9]]), array([[ 2,  3],
           [ 6,  7],
           [10, 11]])]



```python
# 不等量分割
print(A)
t = np.array_split(A, 3, axis=1)
print(np.array_split(A, 3, axis=1))
```

    [[ 0  1  2  3]
     [ 4  5  6  7]
     [ 8  9 10 11]]
    [array([[0, 1],
           [4, 5],
           [8, 9]]), array([[ 2],
           [ 6],
           [10]]), array([[ 3],
           [ 7],
           [11]])]


## copy


```python
# 默认浅拷贝
a = np.arange(4)
b = a
a[1] = 5

print(a)
print(b)
```

    [0 5 2 3]
    [0 5 2 3]



```python
# 深拷贝
a = np.arange(4)
b = a.copy()
a[1] = 5

print(a)
print(b)
```

    [0 5 2 3]
    [0 1 2 3]

