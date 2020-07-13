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