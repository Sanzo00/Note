---

typora-copy-images-to: img\matplotlib

---

[b站视频](https://www.bilibili.com/video/BV1Jx411L7LU)

[Matplotlib.ipynb](https://github.com/Sanzona/files/blob/master/ipynb/Matplotlib%E7%AC%94%E8%AE%B0.ipynb)

## 基本使用


```python
import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-1, 1, 50)
y = x ** 2

plt.plot(x, y)
plt.show()
```


![png](img/matplotlib/output_1_0.png)


## figure


```python
x = np.linspace(-1, 1, 50)
y1 = x ** 2
y2 = x ** 3

# figure1
plt.figure()
plt.plot(x, y1)
# figure2
plt.figure(num=10, figsize=(8,4))
plt.plot(x, y2)

plt.show()
```


![png](img/matplotlib/output_3_0.png)



![png](img/matplotlib/output_3_1.png)



```python
x = np.linspace(-1, 1, 50)
y1 = x ** 2
y2 = x ** 3

# 画在一个图上
plt.figure()
plt.plot(x, y1)
plt.plot(x, y2, color='red', linewidth=2.0, linestyle='--')

plt.show()
```


![png](img/matplotlib/output_4_0.png)


## 坐标轴


```python
x = np.linspace(-1, 10, 50)
y1 = x ** 2
y2 = x + 1

plt.figure()
plt.plot(x, y1)
plt.plot(x, y2, color='red', linewidth=2.0, linestyle='--')

# 设置X、Y范围
plt.xlim((-1, 2))
plt.ylim((-2, 3))

# lable说明
plt.xlabel('I am X')
plt.ylabel('I am Y')

# 单位
new_ticks = np.linspace(-1, 2, 5)
print(new_ticks)
plt.xticks(new_ticks)
plt.yticks([-2, -1.5, -1, 1.22, 3], ['really bad', 'bad', 'normal', 'good', 'really good'])
# 正则表达
plt.yticks([-2, -1.5, -1, 1.22, 3], [r'$really\ bad$', r'$\alpha$', 'normal', 'good', 'really good'])


# 获取当前的axis
ax = plt.gca()

# 隐藏右边和上面的轴
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

# 设置X、Y轴
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')

# 设置X、Y轴位置
ax.spines['bottom'].set_position(('data', 0)) # outward，axes
ax.spines['left'].set_position(('data', 0))



plt.show()
```

    [-1.   -0.25  0.5   1.25  2.  ]



![png](img/matplotlib/output_6_1.png)


## 图例


```python
x = np.linspace(-1, 10, 50)
y1 = x ** 2
y2 = x + 1

plt.figure()
plt.xlim((-1, 2))
plt.ylim((-2, 3))
plt.xlabel('I am X')
plt.ylabel('I am Y')
new_ticks = np.linspace(-1, 2, 5)
print(new_ticks)
plt.xticks(new_ticks)
plt.yticks([-2, -1.5, -1, 1.22, 3], [r'$really\ bad$', r'$\alpha$', 'normal', 'good', 'really good'])

# 设置label
l1, = plt.plot(x, y1, label='blue')
l2, = plt.plot(x, y2, color='red', linewidth=2.0, linestyle='--', label='red')
# 添加图例
# plt.legend()
plt.legend(handles=[l1,l2], labels=['aa', 'bb'], loc='best')

plt.show()
```

    [-1.   -0.25  0.5   1.25  2.  ]



![png](img/matplotlib/output_8_1.png)


## 标注


```python
x = np.linspace(-10, 10, 50)
y = 2*x + 1

plt.figure()
plt.xlim((-3, 3))
plt.ylim((-6, 8))
plt.plot(x, y)

ax = plt.gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')
ax.spines['bottom'].set_position(('data', 0)) # outward，axes
ax.spines['left'].set_position(('data', 0))

x0 = 1
y0 = 2*x0 + 1
# 画点
plt.scatter(x0, y0, s=50, color='b')

# 画线
plt.plot([x0,x0], [y0,0], 'k--', lw=2.5)

# 箭头
plt.annotate(r'$2x+1=%s$' % y0, xy=(x0, y0), xycoords='data', xytext=(+30, -30),
             textcoords='offset points', fontsize=16,
             arrowprops=dict(arrowstyle='<->', connectionstyle="arc3,rad=.2"))

# 注释
plt.text(-4.5, 6, r'$This\ is\ the\ some\ text. \mu\ \sigma_i\ \alpha_t$',
         fontdict={'size': 16, 'color': 'r'})
plt.show()
```


![png](img/matplotlib/output_10_0.png)


## 可见度


```python
import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-3, 3, 50)
y = 0.1*x

plt.figure()
plt.plot(x, y, linewidth=10, zorder=1)
plt.ylim(-2, 2)
ax = plt.gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data', 0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data', 0))

# 设置XY轴的刻度
for label in ax.get_xticklabels() + ax.get_yticklabels():
    # 大小
    label.set_fontsize(12)
    # 背景
    label.set_bbox(dict(facecolor='white', edgecolor='none', alpha=0.5, zorder=2))

plt.show()
```


![png](img/matplotlib/output_12_0.png)


## 散点图


```python
 import matplotlib.pyplot as plt
import numpy as np

n = 1024    # data size

X = np.random.normal(0, 1, n)
Y = np.random.normal(0, 1, n)
T = np.arctan2(Y, X)    # for color later on

plt.scatter(X, Y, s=75, c=T, alpha=.5)

plt.xlim(-1.5, 1.5)
plt.ylim(-1.5, 1.5)

plt.xticks(())  # ignore xticks
plt.yticks(())  # ignore yticks

plt.show()
```


![png](img/matplotlib/output_14_0.png)


## 柱状图


```python
import matplotlib.pyplot as plt
import numpy as np

n = 12
X = np.arange(n)
Y1 = (1 - X / float(n)) * np.random.uniform(0.5, 1.0, n)
Y2 = (1 - X / float(n)) * np.random.uniform(0.5, 1.0, n)

plt.xlim(-.5, n)
plt.xticks(())
plt.ylim(-1.25, 1.25)
plt.yticks(())

# 设置颜色
plt.bar(X, +Y1, facecolor='#9999ff', edgecolor='white')
plt.bar(X, -Y2, facecolor='#ff9999', edgecolor='white')

for x, y in zip(X, Y1):
    # ha: horizontal alignment
    # va: vertical alignment
    plt.text(x, y + 0.05, '%.2f' % y, ha='center', va='bottom')

for x, y in zip(X, Y2):
    # ha: horizontal alignment
    # va: vertical alignment
    plt.text(x, -y - 0.05, '%.2f' % -y, ha='center', va='top')

plt.show()
```


![png](img/matplotlib/output_16_0.png)


## 等高线


```python
import matplotlib.pyplot as plt
import numpy as np

def f(x,y):
    # the height function
    return (1 - x / 2 + x**5 + y**3) * np.exp(-x**2 -y**2)

n = 256
x = np.linspace(-3, 3, n)
y = np.linspace(-3, 3, n)
# 定义网格
X,Y = np.meshgrid(x, y)

# 根据高度分区，分成8份
plt.contourf(X, Y, f(X, Y), 8, alpha=.75, cmap=plt.cm.hot)

# 画等高线
C = plt.contour(X, Y, f(X, Y), 8, colors='black', linewidths=.5)

# lable
plt.clabel(C, inline=True, fontsize=10)

plt.xticks(())
plt.yticks(())
plt.show()
```


![png](img/matplotlib/output_18_0.png)


## 图像


```python
import matplotlib.pyplot as plt
import numpy as np

# image data
a = np.array([0.313660827978, 0.365348418405, 0.423733120134,
              0.365348418405, 0.439599930621, 0.525083754405,
              0.423733120134, 0.525083754405, 0.651536351379]).reshape(3,3)

"""
for the value of "interpolation", check this:
http://matplotlib.org/examples/images_contours_and_fields/interpolation_methods.html
for the value of "origin"= ['upper', 'lower'], check this:
http://matplotlib.org/examples/pylab_examples/image_origin.html
"""
plt.imshow(a, interpolation='nearest', cmap='bone', origin='lower')
plt.colorbar(shrink=.92)

plt.xticks(())
plt.yticks(())
plt.show()
```


![png](img/matplotlib/output_20_0.png)


## 3D数据


```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = Axes3D(fig)
# X, Y value
X = np.arange(-4, 4, 0.25)
Y = np.arange(-4, 4, 0.25)
X, Y = np.meshgrid(X, Y)

# height value
R = np.sqrt(X ** 2 + Y ** 2)
Z = np.sin(R)

# 3D图像
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.get_cmap('rainbow')) 

# 等高线
# zdir表示投影的平面，offset位置
ax.contourf(X, Y, Z, zdir='z', offset=-2, cmap=plt.get_cmap('rainbow'))
ax.set_zlim(-2, 2)

# 手动设置角度
# ax.view_init(elev=10, azim=80)

plt.show()
```

![png](img/matplotlib/output_22_0.png)



调和平均数（倒数平均数）：$2\frac{XY}{X+Y}$

```python
# 调和平均数
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

fig = plt.figure()
ax = Axes3D(fig)

x = np.linspace(0, 1, 20)
y = np.linspace(0, 1, 20)
x, y = np.meshgrid(x, y)
z = 2 * (x*y)/(x+y)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap=plt.get_cmap('rainbow'))

plt.show()
```

![image-20201018235440320](img/matplotlib/image-20201018235440320.png)



3维散点图

```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
 
data = np.random.randint(0, 10, 24).reshape((8, 3))
x = data[:, 0]
y = data[:, 1]
z = data[:, 2] 
 
fig = plt.figure()
ax = Axes3D(fig)
ax.scatter(x, y, z)
 
ax.set_zlabel('Z')
ax.set_ylabel('Y')
ax.set_xlabel('X')
plt.show()
```

![image-20201024000921585](img/matplotlib/image-20201024000921585.png)


## subplot


```python
import matplotlib.pyplot as plt

plt.figure(figsize=(6, 4))

# plt.subplot(n_rows, n_cols, plot_num)
plt.subplot(2, 2, 1)
plt.plot([0, 1], [0, 1])

plt.subplot(222)
plt.plot([0, 1], [0, 2])

plt.subplot(223)
plt.plot([0, 1], [0, 3])

plt.subplot(224)
plt.plot([0, 1], [0, 4])

# 自动调整子图位置
plt.tight_layout()
plt.show()
```


![png](img/matplotlib/output_24_0.png)



```python
plt.figure(figsize=(6, 4))

# plt.subplot(n_rows, n_cols, plot_num)
plt.subplot(2, 1, 1)
# figure splits into 2 rows, 1 col, plot to the 1st sub-fig
plt.plot([0, 1], [0, 1])

plt.subplot(234)
# figure splits into 2 rows, 3 col, plot to the 4th sub-fig
plt.plot([0, 1], [0, 2])

plt.subplot(235)
# figure splits into 2 rows, 3 col, plot to the 5th sub-fig
plt.plot([0, 1], [0, 3])

plt.subplot(236)
# figure splits into 2 rows, 3 col, plot to the 6th sub-fig
plt.plot([0, 1], [0, 4])

# 自动调整子图位置
plt.tight_layout()
plt.show()
```


![png](img/matplotlib/output_25_0.png)



```python
# method 1: subplot2grid
import matplotlib.pyplot as plt

plt.figure()
ax1 = plt.subplot2grid((3, 3), (0, 0), colspan=3)  # stands for axes
ax2 = plt.subplot2grid((3, 3), (1, 0), colspan=2)
ax3 = plt.subplot2grid((3, 3), (1, 2), rowspan=2)
ax4 = plt.subplot2grid((3, 3), (2, 0))
ax5 = plt.subplot2grid((3, 3), (2, 1))

ax1.set_title('ax1_title')
ax1.plot([1, 2], [1, 2])

ax4.scatter([1, 2], [2, 2])
ax4.set_xlabel('ax4_x')
ax4.set_ylabel('ax4_y')

plt.tight_layout()
plt.show()
```


![png](img/matplotlib/output_26_0.png)



```python
# GridSpec
import matplotlib.gridspec as gridspec

plt.figure()
gs = gridspec.GridSpec(3, 3)
# use index from 0
ax6 = plt.subplot(gs[0, :])
ax7 = plt.subplot(gs[1, :2])
ax8 = plt.subplot(gs[1:, 2])
ax9 = plt.subplot(gs[-1, 0])
ax10 = plt.subplot(gs[-1, -2])

plt.tight_layout()
plt.show()
```


![png](img/matplotlib/output_27_0.png)



```python
f, ((ax11, ax12), (ax13, ax14)) = plt.subplots(2, 2, sharex=True, sharey=True)
ax11.scatter([1,2], [1,2])

plt.tight_layout()
plt.show()
```


![png](img/matplotlib/output_28_0.png)


## 画中画


```python
import matplotlib.pyplot as plt

fig = plt.figure()
x = [1, 2, 3, 4, 5, 6, 7]
y = [1, 3, 4, 2, 5, 8, 6]

# below are all percentage
left, bottom, width, height = 0.1, 0.1, 0.8, 0.8
ax1 = fig.add_axes([left, bottom, width, height])  # main axes
ax1.plot(x, y, 'r')
ax1.set_xlabel('x')
ax1.set_ylabel('y')
ax1.set_title('title')

ax2 = fig.add_axes([0.2, 0.6, 0.25, 0.25])  # inside axes
ax2.plot(y, x, 'b')
ax2.set_xlabel('x')
ax2.set_ylabel('y')
ax2.set_title('title inside 1')


# different method to add axes
plt.axes([0.6, 0.2, 0.25, 0.25])
plt.plot(y[::-1], x, 'g')
plt.xlabel('x')
plt.ylabel('y')
plt.title('title inside 2')

plt.show()
```


![png](img/matplotlib/output_30_0.png)


## 次坐标轴


```python
import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0, 10, 0.1)
y1 = 0.05 * x**2
y2 = -1 *y1

fig, ax1 = plt.subplots()

ax2 = ax1.twinx()    # mirror the ax1
ax1.plot(x, y1, 'g-')
ax2.plot(x, y2, 'b-')

ax1.set_xlabel('X data')
ax1.set_ylabel('Y1 data', color='g')
ax2.set_ylabel('Y2 data', color='b')

plt.show()
```


![png](img/matplotlib/output_32_0.png)


## 动画


```python
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

fig, ax = plt.subplots()

x = np.arange(0, 2*np.pi, 0.01)
line, = ax.plot(x, np.sin(x))


def animate(i):
    line.set_ydata(np.sin(x + i/10.0))  # update the data
    return line,


# Init only required for blitting to give a clean slate.
def init():
    line.set_ydata(np.sin(x))
    return line,

# call the animator.  blit=True means only re-draw the parts that have changed.
# blit=True dose not work on Mac, set blit=False
# interval= update frequency
ani = animation.FuncAnimation(fig=fig, func=animate, frames=100, init_func=init,
                              interval=20, blit=False)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
# anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
```


![png](img/matplotlib/output_34_0.png)

