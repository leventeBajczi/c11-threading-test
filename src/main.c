#include <stdio.h>
#include <threads.h>

unsigned int global_number = 1;
mtx_t global_mutex;


int first_thread_funtion(void * data)
{
    unsigned int n;
    unsigned int cnt = 0;
    printf("First thread up\n");
    mtx_lock(&global_mutex);
    while(1)
    {
        n = global_number;
        cnt = 0;
        for(; global_number>0; global_number--)
            if(n%global_number == 0)
                cnt++;
        if(n%1000 == 0)printf("The number %u has %u divisors.\n", n, cnt);
        cnd_signal((cnd_t*)data);
        cnd_wait((cnd_t*)data, &global_mutex);
    }
    return 0;
}

int second_thread_funtion(void * data)
{  
    unsigned int cnt = 2;
    printf("Second thread up\n");
    mtx_lock(&global_mutex);
    while(1)
    {
        cnd_signal((cnd_t*)data);
        cnd_wait((cnd_t*)data, &global_mutex);
        global_number = cnt++;
    }
    return 0;
}


int main(void) {
    thrd_t first_thread_id, second_thread_id;
    int first_thread_return, second_thread_return;
    cnd_t condition;

    cnd_init(&condition);

    mtx_init(&global_mutex, mtx_plain);
    mtx_lock(&global_mutex);
    
    thrd_create(&first_thread_id, first_thread_funtion, &condition);
    thrd_create(&second_thread_id, second_thread_funtion, &condition);

    mtx_unlock(&global_mutex);

    thrd_join(first_thread_id, &first_thread_return);
    thrd_join(second_thread_id, &second_thread_return);

    return first_thread_return || second_thread_return;
}