src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))
CC = gcc
CFLAGS = -m32 -g -Wall

all: $(targets)
$(targets):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(targets)
