#include <stdio.h>
#include <threads.h>

#define NUM_THREADS 5

void do_once()
{
    printf("thread up\n");
}

static int threadData[NUM_THREADS];

static once_flag flag = ONCE_FLAG_INIT;


int threadFunction(void * data) {
    call_once(&flag, do_once);
    printf("cont.");
    return 0;
}

int main(void) {
    thrd_t threadId[NUM_THREADS];

    // init thread data
    for (int i=0; i < NUM_THREADS; ++i)
        threadData[i] = i;

    // start NUM_THREADS amount of threads
    for (int i=0; i < NUM_THREADS; ++i) {
        if (thrd_create(threadId+i, threadFunction, threadData+i) != thrd_success) {
            printf("%d-th thread create error\n", i);
            return 0;
        }
        thrd_sleep(&(struct timespec){.tv_sec=2}, NULL);
    }

    // wait until all threads terminates
    for (int i=0; i < NUM_THREADS; ++i)
        thrd_join(threadId[i], NULL);

    return 0;
}