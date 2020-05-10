CC = gcc
CFLAGS = -m32 -g -Wall
sockfile = $(wildcard *.socket)
obj = $()

all: server client

server: server.o wrap.o
	gcc server.o wrap.o -o server -Wall

client: client.o wrap.o
	gcc client.o wrap.o -o client -Wall

%.o:%.c
	gcc -c $< -Wall

.PHONY: clean
clean:
	rm -rf $(sockfile) server client *.o
