## 基础语法

### print

```python
# 打印到屏幕
print('hello Tom')
print('hello', 'Bob')

# 打印到文件
fp = open('test.txt', 'a')
print('hello!', file=fp)
fp.close()

# 换行
print('hello\nworld')
"""
hello
world
"""

# 制表符
print('hello\tworld') # hello   world

# 回车
print('hello\rworld') # world

# 退格
print('hello\bworld') # hellworld

# \
print('http:\\\\') # http:\\

# 原字符，最后不能是\
print(r'hello\nworld') # hello\nworld

# 保留字
import keyword
print(keyword.kwlist)
"""
['False', 'None', 'True', 'and', 'as', 'assert', 'async', 'await', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
"""
```



### 变量

```python
name = 'Bob'
print('标识:', id(name))
print('类型:', type(name))
print('值:', name)
print(id('Bob'))

"""
标识: 2851856361840
类型: <class 'str'>
值: Bob
2851856361840
"""
```

变量中的值存放在一个内存单元中，内存单元的地址对应一个id，变量实际保存这个id。



### 数据类型

```python
# 整型
print('10进制:', 110)       # 10进制: 110
print('2进制:', 0b110)      # 2进制: 6
print('8进制:', 0o170)      # 8进制: 120
print('16进制:', 0x1EAF)    # 16进制: 7855

# 浮点型
print(1.1+2.2)  # 3.3000000000000003
from decimal import Decimal
print(Decimal('1.1') + Decimal('2.2')) # 3.3

# 布尔类型
T = True
F = False
print(T, F)

# 字符串类型
str1 = 'hello world!'
str2 = "hello world!"
str3 = '''hello
        world!'''
str4 = """hello
        world!"""
print(str1)
print(str2)
print(str3)
print(str4)

# 其他数据类型 -> 字符串
print("hello" +str(123)) # hello123

# 浮点、字符串整数、布尔类型 -> 整数
print(int(1.63))    # 1
print(int('123'))   # 123
print(int(False))   # 0
# print(int('1.23')) not allow

# 整型、字符串数字、布尔类型 -> 浮点型
print(float(2))         # 2.0
print(float('2'))       # 2.0
print(float('1.23'))    # 1.23
print(float(True))      # 1.0
```



### 输入

```
a = int(input("输入a:"))
b = int(input("输入b:"))
print('a + b = ', a+b)
```



### 算术运算

```python
# 算术运算
print(1+1)  # 2
print(1-1)  # 0
print(1*2)  # 2
print(1/2)  # 0.5

# 整除，向下取整
print(9//4)  # 2
print(-9//4) # -3
print(9//-4) # -3

# 取模，被除数-除数*商
print(9%4)  # 1
print(9%-4) # -3
print(-9%4) # 3
```



### 赋值运算

```python
# 链式赋值，浅拷贝
a = b = c = 10
print(a, id(a))
print(b, id(a))
print(c, id(a))
'''
10 140710539465392
10 140710539465392
10 140710539465392
'''

# 参数赋值
a = 10
a += 10     # 20
a -= 10     # 10
a *= 2      # 20
a /= 3      # 6.666666666666667
a //= 2     # 3.0
a %= 2      # 1.0

# 解包赋值
a, b= 1, 2
print(a, b) # 1 2

a, b = b, a
print(a, b) # 2 1
```



### 比较运算符

```python
a, b = 10, 20
print('a > b?', a>b)      # False
print('a < b?', a<b)      # True
print('a >= b?', a>=b)    # False
print('a <= b?', a<=b)    # True

l1 = [1, 2, 3]
l2 = [1, 2, 3]
print('l1 == l2?', l1==l2)      # True，数值比较
print('l1 is l2?', l1 is l2)    # False，id比较
print(l1 is not l2)             # True
print(id(l1), id(l2))           # 1615788849928 1615816075272
```



### 布尔运算符

```python
a, b = 5, 15

print(a < 10 and b < 10)    # False
print(a < 10 or b < 10)     # True

print(not False)            # True
print(not True)             # False

s = 'hello'
print('w' in s)             # False
print('w' not in s)         # True
```









#### 复数

- 复数=实数+虚数
- 虚数部分必须有j
- 可以没有虚部，可以没有实部

  ```python
  3j
  5 + 0j
  2.4 + 5.6j	// (2.4+5.6j)
  type(2.4 + 5.6)	// <class 'complex'>
  ```

- 获取复数的实数部分和虚数部分

  ```python
  复数.real
  复数.imag
  ```

- 复数的共轭

  ```python
  复数.comjugate()
  ```

#### List

- 列表用[]表示，可以包含所有的对象：整数，浮点数，字符串，函数，布尔值，列表，元组，字典


```python
  list.insert(pos, obj)   在pos之前插入obj
  list.extend([])     同时插入多个元素
  list.remove(obj)    删除存在的某个对象
  del list[0:]    删除区间list[-1:]   支持切片
  print(list[0])  可以通过下标访问，不支持通过obj获取位置
```



#### Dictionary

- 字典{key:value}，是键值对的存在
- key不能重复出现，value可以重复
- key是不可变且不可修改，不能用不确定的元素定义
- value可修改为任意对象
- 不支持切片

```python
dic[key] = value	插入
dic.update({'first':1, 'second':2})	插入多个元素
del dic[key]	删除
```



####  Tuple

- 元组中的元素不可修改
- 支持索引，切片

```python
letters = (1, 'a', 'b')
print(letters[1:])
print(letters.index('b'))
```



#### Set

- 无序
- 不支持切片、索引
- 支持集合运算，添加删除

```python
st = {1, 2, 'a', 'c'}
st.add('asdf')
st.discard('c')
```



#### zip()

- 将对象打包成元组并返回元组组成的队列
- 返回对象，在py3中需要用list()解压为列表
- 长度不同，按照最短的

```python
num = [1, 2, 3, 4]
str = ['first', 'second', 'third']
print(list(zip(num, str)))
// [(1, 'first'), (2, 'second'), (3, 'third')]
```

#### sorted

- 可以对所有可迭代的对象进行排序

- iterable:排序对象、key:排序规则、reverse:降序升序

```python
a = [5, 2, 3, 1]
print(sorted(a))
# [1, 2, 3, 5]

def f(x):
    return len(x)
a = [[1, 2, 3], ['a'], [123, 'b']]
print(sorted(a, key=f))
# [['a'], [123, 'b'], [1, 2, 3]]
```

#### 列表解析式

```python
a = []
for i in range(1, 11):
    a.append(i)
    
b = [i for i in range(1, 11)]

a = [i**2 for i in range(1, 10)]
	# [1, 4, 9, 16, 25, 36, 49, 64, 81]
b = [j+1 for j in range(1, 10)]
	# [2, 3, 4, 5, 6, 7, 8, 9, 10]
c = [n for n in range(1, 10) if n % 2 == 0]	
	# [2, 4, 6, 8]
d = [letter.lower() for letter in 'ABCDEFGHI']	
	# ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
e = {i: i+1 for i in range(4)} 						
	# {0: 1, 1: 2, 2: 3, 3: 4}
f = {i: j for i, j in zip(range(1, 6), 'abcde')}		
	# {1: 'a', 2: 'b', 3: 'c', 4: 'd', 5: 'e'}
g = {i: j.upper() for i, j in zip(range(1, 6), 'abcde')}  
	# {1: 'A', 2: 'B', 3: 'C', 4: 'D', 5: 'E'}

```



#### string.strip()  去除字符串头尾的字符

```py
s = '00aa00aa00'
print(s.strip('0'))	#aa00aa

#去除字符串的标点符号
import string
s = s.strip(string.punctuation)
```