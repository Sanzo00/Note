src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

all:  server client epoll  nonblock_epoll epoll_loop

server: server.o wrap.o
	gcc server.o wrap.o -o server -Wall 

client: client.o wrap.o
	gcc client.o -o client -Wall

nonblock_epoll: nonblock_epoll.o
	gcc $< -o nonblock_epoll -Wall

epoll: epoll.o
	gcc $< -o epoll -Wall

epoll_loop: epoll_loop.o
	gcc $< -o epoll_loop -Wall

%.o:%.c
	gcc -c $< -Wall

.PHONY: clean
clean:
	rm -rf $(targets) *.o
