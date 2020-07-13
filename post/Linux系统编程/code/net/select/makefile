src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

all:  server client

server: server.o wrap.o
	gcc server.o wrap.o -o server -Wall 

client: client.o wrap.o
	gcc client.o wrap.o -o client -Wall

%.o:%.c
	gcc -c $< -Wall

.PHONY: clean
clean:
	rm -rf $(targets)
