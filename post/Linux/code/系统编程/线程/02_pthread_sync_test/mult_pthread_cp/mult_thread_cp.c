#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define T_NUM 5
#define ITEMS 50

void err_sys(void *str)
{
	perror(str);
	exit(1);
}

void err_usr(char *str)
{
	fputs(str, stderr);
	exit(1);
}

typedef struct{
	int off, size, t_no;
}arg_t;

char *s, *d;
int *done;
int n = T_NUM;

//arg{off, size, t_no;}
void *tfn(void *arg)
{
	arg_t *arg_p; int i;
	char *p, *q;

	arg_p = (arg_t *)arg;
	p = s + arg_p->off, q = d + arg_p->off;
	for(i = 0; i < arg_p->size; i++)
	{
		/* 逗号表达式的使用技巧*/
		*q++ = *p++, done[arg_p->t_no]++;
		usleep(10);
	}

	return NULL;
}

void *display(void *arg)
{
	int size, interval, draw, sum, i, j;

	size = (int)arg;
	interval = size / (ITEMS - 1);
	draw = 0;
	while(draw < ITEMS){
		for(i = 0, sum = 0; i < n; i++)
			sum += done[i];
		j = sum / interval + 1;
		for(; j > draw; draw++){
			putchar('='); fflush(stdout);
		}
	}
	putchar('\n');

	return NULL;
}

int main(int argc, char *argv[])
{
	int src, dst, i, len, off;
	struct stat statbuf;
	pthread_t *tid;
	arg_t *arr;

	if(argc != 3 && argc != 4)
		err_usr("usage : cp src dst [thread_no]\n");
	if(argc == 4)
		n = atoi(argv[3]);

	src = open(argv[1], O_RDONLY);
	if(src == -1)
		err_sys("fail to open");
	dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(dst == -1)
		err_sys("fail to open");

	if(fstat(src, &statbuf) == -1)
		err_sys("fail to stat");

	lseek(dst, statbuf.st_size - 1, SEEK_SET);
	write(dst, "a", 1);                          //IO操作拓展文件大小,也可以使用truncate

	s = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, src, 0);
	if(s == MAP_FAILED)
		err_sys("fail to mmap");
	d = (char *)mmap(NULL, statbuf.st_size, PROT_WRITE , MAP_SHARED, dst, 0);
	if(d == MAP_FAILED)
		err_sys("fail to mmap");

	close(src); close(dst);
    //pthread_t tid[n+1];
	tid = (pthread_t *)malloc(sizeof(pthread_t) * (n + 1));
	if(tid == NULL)
		err_sys("fail to malloc");
    //int done[n]  每个线程完成任务字节数
	done = (int *)calloc(sizeof(int), n);
	if(done == NULL)
		err_sys("fail to malloc");
    //arr[n] 每个线程的任务
	arr = (arg_t *)malloc(sizeof(arg_t) * n);
	if(arr == NULL)
		err_sys("fail to malloc");

    //构建线程任务数组，分配任务
	len = statbuf.st_size / n, off = 0;
	for(i = 0; i < n; i++, off += len) 
		arr[i].off = off, arr[i].size = len, arr[i].t_no = i; 
	arr[n - 1].size += (statbuf.st_size % n);
    
    //创建执行拷贝任务线程
	for(i = 0; i < n; i++)
		pthread_create(&tid[i], NULL, tfn, (void *)&arr[i]);

    //创建进度线程
	pthread_create(&tid[n], NULL, display, (void *)statbuf.st_size);

	for(i = 0; i < n + 1; i++)
		pthread_join(tid[i], NULL);
#if 1 
	munmap(s, statbuf.st_size);
	munmap(d, statbuf.st_size);
#endif
	free(tid); free(done); free(arr);

	return 0;
}

