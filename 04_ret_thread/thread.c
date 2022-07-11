#include <stdio.h>
#include <errno.h>   //使用宏 ESRCH
#include <pthread.h>
//线程执行的函数
//对于一个默认属性的线程 A 来说，线程占用的资源并不会因为执行结束而得到释放。
//而通过在其它线程中执行pthread_join(A,NULL);语句，可以轻松实现“及时释放线程 A 所占资源”的目的。 
void *ThreadFun(void *arg)
{
    pthread_exit("http://c.biancheng.net");
}
int main()
{
    int res;
    void * thread_result;
    pthread_t myThread;
    //创建 myThread 线程
    res = pthread_create(&myThread, NULL, ThreadFun, NULL);
    if (res != 0) {
        printf("线程创建失败\n");
        return 0;
    }
    //阻塞主线程，等待 myThread 线程执行结束
    res = pthread_join(myThread, &thread_result);
    if (res != 0) {
        printf("1：等待线程失败\n");
    }
    //输出获取到的 myThread 线程的返回值
    printf("%s\n", (char*)thread_result);

    //尝试再次获取 myThread 线程的返回值
    res = pthread_join(myThread, &thread_result);
    /*
    EDEADLK：检测到线程发生了死锁。
    EINVAL：分为两种情况，要么目标线程本身不允许其它线程获取它的返回值，要么事先就已经有线程调用 pthread_join() 函数获取到了目标线程的返回值。
    ESRCH：找不到指定的 thread 线程。
    */
    if (res == ESRCH) {
        printf("2：等待线程失败，线程不存在\n");
    }
    return 0;
}