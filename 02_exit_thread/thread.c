#include <stdio.h>
#include <unistd.h>   //调用 sleep() 函数
#include <pthread.h>

void *ThreadFun(void *arg)
{
    sleep(5);//等待一段时间
    printf("http://c.biancheng.net\n");
}

int main()
{
    int res;
    pthread_t myThread;
    
    res = pthread_create(&myThread, NULL, ThreadFun, NULL);
    if (res != 0) {
        printf("线程创建失败");
        return 0;
    }
    printf("C语言中文网\n");
    //return 会结束整个程序的执行
    //pthread_exit 只会结束当前线程 对其他线程执行无影响
    pthread_exit(NULL);
    // return 0;
}