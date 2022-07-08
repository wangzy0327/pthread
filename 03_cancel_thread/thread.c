#include <stdio.h>
#include <pthread.h>    //PTHREAD_CANCELED
#include <unistd.h>   //调用 sleep() 函数
#include <stdlib.h>     // sleep() 函数
//线程执行的函数
void * thread_Fun(void * arg) {
    printf("新建线程开始执行\n");
    sleep(10);
}

int main()
{
    pthread_t myThread;
    void * mess;
    int value;
    int res;
    //创建 myThread 线程
    res = pthread_create(&myThread, NULL, thread_Fun, NULL);
    if (res != 0) {
        printf("线程创建失败\n");
        return 0;
    }
    sleep(1);
    //向 myThread 线程发送 Cancel 信号
    res = pthread_cancel(myThread);
    if (res != 0) {
        printf("终止 myThread 线程失败\n");
        return 0;
    }
    //获取已终止线程的返回值
    res = pthread_join(myThread, &mess);
    if (res != 0) {
        printf("等待线程失败\n");
        return 0;
    }
    //如果线程被强制终止，其返回值为 PTHREAD_CANCELED
    if (mess == PTHREAD_CANCELED) {
        printf("myThread 线程被强制终止\n");
    }
    else {
        printf("error\n");
    }
    return 0;
}