#include <stdio.h>
#include <unistd.h>   //调用 sleep() 函数
#include <pthread.h>  //调用 pthread_create() 函数
#include <errno.h>    //线程创建异常状态 EAGAIN EINVAL EPERM
#include <stdlib.h>   //exit(1)

void *ThreadFun(void *arg)
{
    if (arg == NULL) {
        printf("arg is NULL\n");
    }
    else {
        printf("%s\n", (char*)arg);
    }
    return NULL;
}

void CheckStatus(int status){
    if(status == 0){
        return ;
    }else if(status == EAGAIN){
        printf("系统资源不足，无法提供创建线程所需的资源");
    }else if(status == EINVAL){
        printf("传递给pthread_create() 函数的 attr 参数无效");
    }else if(status == EPERM){
        printf("传递给 pthread_create() 函数的 attr 参数中，某些属性的设置为非法操作，程序没有相关的设置权限");
    }else{
        printf("其他线程创建失败错误！错误状态码为 %d 请查看errno.h",status);
    }
    exit(1);
}

int main()
{
    int res;
    char * url = "http://www.biancheng.net";
    //定义两个表示线程的变量（标识符）
    pthread_t myThread1,myThread2;
    //创建 myThread1 线程
    res = pthread_create(&myThread1, NULL, ThreadFun, NULL);
    // if (res != 0) {
    //     printf("线程创建失败");
    //     return 0;
    // }
    CheckStatus(res);
    sleep(5);  //令主线程等到 myThread1 线程执行完成
    
    //创建 myThread2 线程
    res = pthread_create(&myThread2, NULL, ThreadFun,(void*)url);
    // if (res != 0) {
    //     printf("线程创建失败");
    //     return 0;
    // }
    CheckStatus(res);
    sleep(5); // 令主线程等到 mythread2 线程执行完成
    return 0;
}