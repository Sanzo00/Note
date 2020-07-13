# __thread

__thread修饰的变量，在每个线程中都有一份独立实体，每个线程互不干扰，可以修饰全局性且值可能改变的变量

```c
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
// static __thread int i = 1;	// 修饰static变量
__thread int i = 1;	// 修饰全局变量

void* work1(void* arg) {
	cout << ++i << endl;	// 输出2
	return NULL;
}

void* work2(void* arg) {
	sleep(1);	// 等待线程work1修改i之后，继续work2	
	cout << ++i << endl;	// 输出2
	return NULL;
}

int main() {
	pthread_t pid1, pid2;
	pthread_create(&pid1, NULL, work1, NULL);
	pthread_create(&pid2, NULL, work2, NULL);
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	cout << i << endl;	// 输出1

	return 0;
}
```

