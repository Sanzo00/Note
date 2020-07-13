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
.PHONY:clean
clean:
	rm $(obj) $(target) -f

hello:
	echo "123"
