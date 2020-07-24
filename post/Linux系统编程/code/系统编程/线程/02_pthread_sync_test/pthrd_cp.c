#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct{
	int off;
	int size;
}arg_t;

char *s, *d;

void *tfn(void *arg)
{
	arg_t *p; int i;

	p = (arg_t *)arg;

	for (i = 0; i < p->size; i++)
		d[p->off+i] = s[p->off+i];

	return NULL;
}

#if 0
int main(int argc, char *argv[])
{
	int n = 5, i, off, size;
	int in, out;
	struct stat statbuf;
	pthread_t *tid;
	arg_t *p;

	if (argc == 4)
		n = atoi(argv[3]);

	in = open(argv[1], O_RDONLY);
	if (in == -1) {
		perror("open src error");
		exit(1);
	}
	out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (in == -1) {
		perror("open dst error");
		exit(1);
	}
	if (stat(argv[1], &statbuf) == -1) {
		perror("stat error");
		exit(1);
	}

	lseek(out, statbuf.st_size-1, SEEK_SET);
	write(out, "a", 1);

	s = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, in, 0);
	if (s == MAP_FAILED) {
		perror("mmap src error");
		exit(1);
	}
	d = mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_SHARED, out, 0);
	if (d == MAP_FAILED) {
		perror("mmap dst error");
		exit(1);
	}
	close(in); close(out);

	tid = malloc(sizeof(pthread_t)*n);
	if (tid == NULL) {
		printf("tid malloc fail\n");
		exit(1);
	}
	p = malloc(sizeof(arg_t)*n);
	if (p == NULL) {
		printf("p malloc fail\n");
		exit(1);
	}

	size = statbuf.st_size / n;
	for (i = 0, off = 0; i < n; i++, off += size) {
		p[i].off = off;
		p[i].size = size;
	}
	p[n-1].size += statbuf.st_size % n;	

	for (i = 0; i < n; i++) 
		pthread_create(&tid[i], NULL, tfn, (void *)&p[i]);

	for (i = 0; i < n; i++) 
		pthread_join(tid[i], NULL);

	munmap(s, statbuf.st_size);
	munmap(d, statbuf.st_size);

	return 0;
}

#else
int main(int argc, char *argv[])
{
	int n = 5, i, off, size;
	int in, out;
	struct stat statbuf;
	pthread_t *tid;
	arg_t *p;

	if (argc == 4)
		n = atoi(argv[3]);

	in = open(argv[1], O_RDONLY);
	out = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0644);
	stat(argv[1], &statbuf);

	lseek(out, statbuf.st_size-1, SEEK_SET);
	write(out, "a", 1);

	s = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, in, 0);
	d = mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_SHARED, out, 0);
	close(in); close(out);

	tid = malloc(sizeof(pthread_t)*n);
	p = malloc(sizeof(arg_t)*n);

	size = statbuf.st_size / n;
	for (i = 0, off = 0; i < n; i++, off += size) {
		p[i].off = off;
		p[i].size = size;
	}
	p[n-1].size += statbuf.st_size % n;	/*最后一个线程包圆*/

	for (i = 0; i < n; i++) 
		pthread_create(&tid[i], NULL, tfn, (void *)&p[i]);

	for (i = 0; i < n; i++) 
		pthread_join(tid[i], NULL);

	munmap(s, statbuf.st_size);
	munmap(d, statbuf.st_size);

	return 0;
}

#endif
