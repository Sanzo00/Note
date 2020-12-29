all: threadpool

threadpool: threadpool.c
	gcc $< -o threadpool -Wall -lpthread
	
.PHONY: clean
clean:
	rm threadpool
