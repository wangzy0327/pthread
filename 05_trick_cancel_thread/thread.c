#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * thread_Fun1(void * arg) {
    printf("新建线程开始执行\n");
    //插入无限循环的代码，测试 pthread_cancel()函数的有效性
    while(1);
}

void * thread_Fun2(void * arg) {
    printf("新建线程开始执行\n");
    int res;
    //设置线程为可取消状态
    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (res != 0) {
        printf("修改线程可取消状态失败\n");
        return  NULL;
    }
    //设置线程接收到 Cancel 信号后立即结束执行
    res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    if (res != 0) {
        printf("修改线程响应 Cancel 信号的方式失败\n");
        return  NULL;
    }
    while (1);
    return NULL;
}

int main()
{
    pthread_t myThread;
    void * mess;
    int value;
    int res;
    // res = pthread_create(&myThread, NULL, thread_Fun1, NULL);
    res = pthread_create(&myThread, NULL, thread_Fun2, NULL);
    if (res != 0) {
        printf("线程创建失败\n");
        return 0;
    }
    sleep(1);
    //令 myThread 线程终止执行
    res = pthread_cancel(myThread);
    if (res != 0) {
        printf("终止 myThread 线程失败\n");
        return 0;
    }
    printf("等待 myThread 线程执行结束：\n");
    res = pthread_join(myThread, &mess);
    if (res != 0) {
        printf("等待线程失败\n");
        return 0;
    }
    if (mess == PTHREAD_CANCELED) {
        printf("myThread 线程被强制终止\n");
    }
    else {
        printf("error\n");
    }
    return 0;
    /**
     * @res
     * 新建线程开始执行
        等待 myThread 线程执行结束：
     * 对于默认属性的线程，当有线程借助 pthread_cancel() 函数向它发送 Cancel 信号时，它并不会立即结束执行，而是选择在一个适当的时机结束执行
       当线程执行一些特殊的函数时，会响应 Cancel 信号并终止执行，比如常见的 pthread_join()、pthread_testcancel()、sleep()、system() 等，
       POSIX 标准称此类函数为“cancellation points”（中文可译为“取消点”）

     * 
        新建线程开始执行
        myThread 线程被强制终止
     */
}