src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CC = gcc
#CFLAGS = -m32 -g -Wall -lpthread 
CFLAGS = -g -Wall -lpthread 

all:$(targets)

$(targets):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) 

