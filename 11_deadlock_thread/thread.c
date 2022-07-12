#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex2;

void *func1(void *args)
{
    pthread_mutex_lock(&mutex);
    printf("t1 成功申请 mytex 锁\n");
    sleep(2);
    pthread_mutex_lock(&mutex2);
    printf("t1 成功申请 mytex2 锁\n");
    printf("%lu is running\n",pthread_self());
    pthread_mutex_unlock(&mutex);
    printf("------%lu done\n",pthread_self());      
}

void *func2(void *args)
{ 
    pthread_mutex_lock(&mutex2);
    printf("t2 成功申请 mytex2 锁\n");
    sleep(2);
    pthread_mutex_lock(&mutex);
    printf("t2 成功申请 mytex 锁\n");
    printf("%lu is running\n",pthread_self()); 
    pthread_mutex_unlock(&mutex);
    printf("------%lu done\n",pthread_self());
}

int main()
{
    int ret;
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex2,NULL);

    ret = pthread_create(&t1, NULL, func1, NULL);
    if(ret != 0){
           printf("create t1 fail\n");
    }

    ret = pthread_create(&t2, NULL, func2, NULL);
    if(ret != 0){
           printf("create t2 fail\n");
    }
  
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);
    //  t1 和 t2 都发生了死锁
    return 0;
}