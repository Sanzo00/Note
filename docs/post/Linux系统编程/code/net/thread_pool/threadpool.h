#ifndef __THREADPOLL_H_
#define __THREADPOLL_H_

typedef struct threadpool_t threadpool_t;

threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);
int threadpool_add(threadpool_t *pool, void*(*function)(void *arg), void *arg);
int threadpool_destroy(threadpool_t *pool);
int threadpool_all_threadnum(threadpool_t *poll);
int threadpool_busy_threadnum(threadpool_t *poll);

#endif
