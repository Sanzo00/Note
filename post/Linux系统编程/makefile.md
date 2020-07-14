## 普通版

```bash
app: main.o sum.o sub.o
     gcc main.o sum.o sub.o -o app

main.o: main.c
	gcc -c main.c

sum.o: sum.c
	gcc -c sum.c

sub.o: sub.c
	gcc -c sub.c
```



## 自动变量

```bash
$@: 规则中的目标
$<: 规则中的第一个依赖
$^: 规则中的所有依赖
```

```bash
obj = main.o sum.o sub.o
target = app
# makefile系统变量
CC = gcc

$(target):$(obj)
$(CC) $(obj) -o $(target)

%.o: %.c
$(CC) -c $< -o $@
```

makefile函数

```bash
target = app

# 得到所有.c文件
src = $(wildcard ./*.c)

# 将.c替换为.o
obj = $(patsubst ./%.c, ./%.o, $(src))

CC = gcc

$(target): $(obj)
	$(CC) $(obj) -o $(target)

%.o: %.c
	$(CC) -c $< -o $@
	
# 声明伪目标
.PHONY:clean
clean:
	rm $(obj) $(target)
```

## 静态模型

$(objects): %.o:%.c

目标从$(objects)中获取， "%.o"表示以".o"结尾的目标, 即foo.o bar.o, 依赖模式就是把"%.o"中的"%"拿来加上".c"

```bash
objects = foo.o bar.o
all: $(objects)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) &< -o $@
```

等价于

```bash
foo.o : foo.c
$(CC) -c $(CFLAGS) foo.c -o foo.o

bar.o : bar.c
$(CC) -c $(CFLAGS) bar.c -o bar.o
```

