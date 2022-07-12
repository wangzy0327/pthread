#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // sleep()
#include <errno.h>
//myThread1 线程执行的函数
void *Thread1(void *arg)
{
    printf("Thread1 正在执行\n");
    printf("http://c.biancheng.net\n");
    printf("Thread1 执行完毕\n");
    return NULL;
}
//myThread2 线程执行的函数
void* Thread2(void* arg)
{
    printf("Thread2 正在执行\n");
    printf("C语言中文网\n");
    printf("Thread2 执行完毕\n");
    return NULL;
}

void CheckStatus(int status){
    switch (status)
    {
        case EPERM:
            printf("Operation not permitted\n");
            break;
        case ENOENT:
            printf("No such file or directory\n");
            break;
        case ESRCH:
            printf("No such process\n");
            break;
        case EINTR:
            printf("Interrupted system call\n");
            break;
        case EIO:
            printf("I/O error\n");
            break;
        case ENXIO:
            printf("No such device or address\n");
            break;
        case E2BIG:
            printf("Argument list too long\n");
            break;
        case ENOEXEC:
            printf("Exec format error\n");
            break;
        case EBADF:
            printf("Operation not permitted\n");
            break;
        case ECHILD:
            printf("No child processes\n");
            break;
        case EAGAIN:
            printf("Try again\n");
            break;
        case ENOMEM:
            printf("Out of memory \n");
            break;
        case EACCES:
            printf("Permission denied\n");
            break;
        case EFAULT:
            printf("Bad address\n");
            break;
        case ENOTBLK:
            printf("Block device required\n");
            break;
        case EBUSY:
            printf("Device or resource busy\n");
            break;
        case EEXIST:
            printf("File exists \n");
            return ;
        case EXDEV:
            printf("Cross-device link\n");
            break;
        case ENODEV:
            printf("No such device\n");
            break;
        case ENOTDIR:
            printf("Not a directory\n");
            break;
        case EISDIR:
            printf("Is a directory\n");
            break;
        case EINVAL:
            printf("File table overflow\n");
            break;
        case ENFILE:
            printf("No such device or address\n");
            break;
        case EMFILE:
            printf("Too many open files\n");
            break;
        case ENOTTY:
            printf("Not a typewriter\n");
            break;
        case ETXTBSY:
            printf("Text file busy\n");
            break;
        case EFBIG:
            printf("File too large\n");
            break;
        case ENOSPC:
            printf("No space left on device\n");
            break;
        case ESPIPE:
            printf("Illegal seek \n");
            break;
        case EROFS:
            printf("Read-only file system\n");
            break;
        case EMLINK:
            printf("Too many links\n");
            break;
        case EPIPE:
            printf("Broken pipe\n");
            break;
        case EDOM:
            printf("Math argument out of domain of func\n");
            break;
        case ERANGE:
            printf("Math result not representable\n");
            break;            
    default:
        printf("线程创建成功！\n");
        return ;
    }
    // if(status == 0){
    //     return ;
    // }else if(status == EAGAIN){
    //     printf("系统资源不足，无法提供创建线程所需的资源");
    // }else if(status == EINVAL){
    //     printf("传递给pthread_create() 函数的 attr 参数无效");
    // }else if(status == EPERM){
    //     printf("传递给 pthread_create() 函数的 attr 参数中，某些属性的设置为非法操作，程序没有相关的设置权限");
    // }else{
    //     printf("其他线程创建失败错误！错误状态码为 %d 请查看errno.h",status);
    // }
    exit(1);
}

/**
 * @brief sudo ./12_self_property_thread 3 30
 * 
 * @param argc 
 * @param argv 
 * @return int 
 * 
 * 
 * 执行时需要使用 管理员权限来执行，不然会出现Operation not permitted的错误
   Thread2 正在执行
    C语言中文网
    Thread2 执行完毕
    Thread1 正在执行
    http://c.biancheng.net
    Thread1 执行完毕
    mythread1不支持调用 pthread_join()函数
    主线程执行完毕
 * 
 */

int main(int argc,char *argv[])
{
    int num1, num2, res;
    //创建两个线程
    pthread_t mythread1, mythread2;
    //创建两个表示线程优先级的变量
    struct  sched_param param1, param2;
    //创建两个表示线程属性的变量
    pthread_attr_t myAttr1, myAttr2;
    //接收 2 个整数，用于设定线程的优先级
    if (argc != 3) {
        printf("未向程序传入 2 个表示优先级的数字\n");
        return 0;
    }
    //初始化线程属性
    res = pthread_attr_init(&myAttr1);
    if (res != 0) {
        printf("myAttr1 init Fail\n");
    }
   
    res = pthread_attr_init(&myAttr2);
    if (res != 0) {
        printf("myAttr1 init Fail\n");
    }

    //设置 myAttr1 的 __detachstate 属性值为 PTHREAD_CREATE_DETACHED
    //遵循 myAttr1 属性的线程执行函数完毕后会自行释放占用私有资源，不支持 pthread_join() 函数
    res = pthread_attr_setdetachstate(&myAttr1, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        printf("myAttr1 set_detachstate Fail\n");
    }
    //设置 myAttr1 的 __scope 属性值为 PTHREAD_SCOPE_SYSTEM
    //遵循 myAttr1 属性的线程将同系统中的所有其它线程争夺 CPU 资源
    res = pthread_attr_setscope(&myAttr1, PTHREAD_SCOPE_SYSTEM);
    if (res != 0) {
        printf("myAttr1 set_scope Fail\n");
    }
    //设置 myAttr2 的 __scope 属性值为 PTHREAD_SCOPE_SYSTEM
    //遵循 myAttr2 属性的线程将同系统中的所有其它线程争夺 CPU 资源
    res = pthread_attr_setscope(&myAttr2, PTHREAD_SCOPE_SYSTEM);
    if (res != 0) {
        printf("myAttr2 set_scope Fail\n");
    }

    //设置 myAttr1 的 __schedpolicy 属性值为 SCHED_FIFO
    //系统会以实时调用的方式执行遵循 myAttr1 属性的线程
    res = pthread_attr_setschedpolicy(&myAttr1, SCHED_FIFO);
    if (res != 0) {
        printf("myAttr1 set_policy Fail\n");
    }
   
    //设置 myAttr2 的 __schedpolicy 属性值为 SCHED_FIFO
    //系统会以实时调用的方式执行遵循 myAttr2 属性的线程
    res = pthread_attr_setschedpolicy(&myAttr2, SCHED_FIFO);
    if (res != 0) {
        printf("myAttr2 set_policy Fail\n");
    }

    //设置 myAttr1 的 __inheritsched 属性值为 PTHREAD_EXPLICIT_SCHED
    //myAttr1 属性的线程将遵循自定义的线程属性
    res = pthread_attr_setinheritsched(&myAttr1, PTHREAD_EXPLICIT_SCHED);
    if (res != 0) {
        printf("myAttr1 set_inheritsched fail\n");
    }
   
    //设置 myAttr2 的 __inheritsched 属性值为 PTHREAD_EXPLICIT_SCHED
    //myAttr2 属性的线程将遵循自定义的线程属性
    res = pthread_attr_setinheritsched(&myAttr2, PTHREAD_EXPLICIT_SCHED);
    if (res != 0) {
        printf("myAttr2 set_inheritsched fail\n");
    }

    //想 argv[] 数组中的字符转换为数字
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);
    // 分别将 num1 和 num2 作为线程优先级的值
    param1.sched_priority = num1;
    param2.sched_priority = num2;
    //设置 myAttr1 属性的优先级为 param1
    res = pthread_attr_setschedparam(&myAttr1, &param1);
    if (res != 0) {
        printf("param1 setscheparam Fail\n");
    }
    //设置 myAttr2 属性的优先级为 param2
    res = pthread_attr_setschedparam(&myAttr2, &param2);
    if (res != 0) {
        printf("param2 setscheparam Fail\n");
    }
    //创建新线程并遵循 myAttr1 属性
    res = pthread_create(&mythread1, &myAttr1, Thread1, NULL);
    if (res != 0) {
        printf("mythread1 线程创建错误状态码：%d\n",res);
        printf("mythread1 create Fail\n");
    }
    //创建新线程并遵循 myAttr2 属性
    res = pthread_create(&mythread2, &myAttr2, Thread2, NULL);
    if (res != 0) {
        printf("mythread1 线程创建错误状态码：%d\n",res);
        printf("mythread2 create Fail\n");
    }
    sleep(5);  //等待 mythread1 和 mythread2 两个线程执行完
    //尝试 pthread_join() 函数等待 mythread1 线程执行结束
    res = pthread_join(mythread1, NULL);
    if (res != 0) {
        if (res == EINVAL) {
            printf("mythread1不支持调用 pthread_join()函数\n");
        }
    }
    //尝试等待 mythread2 线程执行结束
    res = pthread_join(mythread2, NULL);
    if (res != 0) {
        printf("mythread2 has finished\n");
    }
    printf("主线程执行完毕\n");
    return 0;
}

/*
线程属性
typedef struct
{
       int __detachstate;
       int __schedpolicy;
       struct sched_param __schedparam;
       int __inheritsched;
       int __scope;
       size_t __guardsize;
       int __stackaddr_set;
       void* __stackaddr;
       size_t __stacksize;
} pthread_attr_t;

*/
/**
   1) __detachstate
    __detachstate 属性值用于指定线程终止执行的时机，该属性的值有两个，分别是：
    PTHREAD_CREATE_JOINABLE（默认值）：线程执行完函数后不会自行释放资源；
    PTHREAD_CREATE_DETACHED：线程执行完函数后，会自行终止并释放占用的资源。

   2) __schedpolicy
    __schedpolicy 属性用于指定系统调度该线程所用的算法，它的值有以下 3 个：
    SCHED_OTHER（默认值）：分时调度算法；
    SCHED_FIFO：先到先得（实时调度）算法；
    SCHED_RR：轮转法；

   3)__schedparam
    __scheparam 用于设置线程的优先级（默认值为 0），该属性仅当线程的 __schedpolicy 属性为 SCHED_FIFO 或者 SCHED_RR 时才能发挥作用。

   4) __inheritsched
    新建线程的调度属性（____schedpolicy 和 __schedparam 属性）默认遵循父线程的属性（谁创建它，谁就是它的父线程），如果我们想自定义线程的调度属性，就需要借助 __inheritsched 属性。

   5) __scope
    线程执行过程中，可以只和同进程内的其它线程争夺 CPU 资源，也可以和系统中所有的其它线程争夺 CPU 资源，__scope 属性用于指定目标线程和哪些线程抢夺 CPU 资源

    当调用 pthread_attr_setscope() 函数时，scope 参数的可选值有两个，分别是：
        PTHREAD_SCOPE_PROCESS：同一进程内争夺 CPU 资源；
        PTHREAD_SCOPE_SYSTEM：系统所有线程之间争夺 CPU 资源。
    Linux系统仅支持 PTHREAD_SCOPE_SYSTEM，即所有线程之间争夺 CPU 资源。

   6) __stacksize

    每个线程都有属于自己的内存空间，通常称为栈（有时也称堆栈、栈空间、栈内存等）。
    某些场景中，线程执行可能需要较大的栈内存，此时就需要我们自定义线程拥有的栈的大小。

   7) __guardsize
    每个线程中，栈内存的后面都紧挨着一块空闲的内存空间，我们通常称这块内存为警戒缓冲区

    它的功能是：一旦我们使用的栈空间超出了额定值，警戒缓冲区可以确保线程不会因“栈溢出”立刻执行崩溃。

 */ 