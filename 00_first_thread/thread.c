#include <stdio.h>
#include <pthread.h>

//定义线程要执行的函数，arg 为接收线程传递过来的数据
void* Thread1(void *arg)
{
    printf("http://c.biancheng.net\n");
    return "Thread1成功执行";
}
//定义线程要执行的函数，arg 为接收线程传递过来的数据
void* Thread2(void* arg)
{
    printf("C语言中文网\n");
    return "Thread2成功执行";
}

int main()
{
    int res;
    pthread_t mythread1, mythread2;
    void* thread_result;
    /*创建线程
    &mythread:要创建的线程
    NULL：不修改新建线程的任何属性
    ThreadFun:新建线程要执行的任务
    NULL：不传递给 ThreadFun() 函数任何参数

    返回值 res 为 0 表示线程创建成功，反之则创建失败。
    */
    res = pthread_create(&mythread1, NULL, Thread1, NULL);
    if (res != 0) {
        printf("线程创建失败");
        return 0;
    }

    res = pthread_create(&mythread2, NULL, Thread2, NULL);
    if (res != 0) {
        printf("线程创建失败");
        return 0;
    }
    /*
    等待指定线程执行完毕
    mtThread:指定等待的线程
    &thead_result:接收 ThreadFun() 函数的返回值，或者接收 pthread_exit() 函数指定的值

    返回值 res 为 0 表示函数执行成功，反之则执行失败。
    */
    res = pthread_join(mythread1, &thread_result);
    //输出线程执行完毕后返回的数据
    printf("Thread1 返回值 : %s\n", (char*)thread_result);
   
    res = pthread_join(mythread2, &thread_result);
    printf("Thread2 返回值 : %s\n", (char*)thread_result);
    printf("主线程执行完毕");
    return 0;
}