#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *worker(void *arg)
{
    printf("Worker: locking mutex\n");
    pthread_mutex_lock(&lock);

    printf("Worker: waiting on condition variable...\n");
    // This will:
    // 1. unlock the mutex
    // 2. put the thread to sleep in kernel
    // 3. when signaled, wake up and re-lock the mutex before returning
    pthread_cond_wait(&cond, &lock);

    printf("Worker: woke up! finishing.\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t t;
    pthread_create(&t, NULL, worker, NULL);

    sleep(10); // give time for worker to sleep

    printf("Main: sending signal\n");
    pthread_cond_signal(&cond);

    pthread_join(t, NULL);

    printf("Main: done\n");
    return 0;
}