#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
//初始化互斥锁
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
//使用初始化函数来初始化互斥锁 
//pthread_mutex_t myMutex;
//pthread_mutex_init(&myMutex , NULL);
//初始化条件变量
pthread_cond_t myCond = PTHREAD_COND_INITIALIZER;
//使用初始化函数来初始化条件变量
// pthread_cond_t myCond;
// pthread_cond_init(&myCond, NULL);

//设置全局变量
int x = 0;
//线程执行的函数
//直到x == 10的时候执行  pthread_cond_wait阻塞，直到pthread_cond_signal打开
void * waitForTrue(void *args) {
    int res;
    //条件变量阻塞线程之前，先对互斥锁执行“加锁”操作
    res = pthread_mutex_lock(&myMutex);
    if (res != 0) {
        printf("waitForTrue 加锁失败\n");
        return NULL;
    } 
    printf("%lu waitForTrue --- 等待 x 的值为 10\n",pthread_self());
    //在cond_wait的时候会释放mutex锁，等待状态改变
    if (pthread_cond_wait(&myCond, &myMutex) == 0) {
        printf("%lu waitForTrue  x = %d\n",pthread_self(), x);
    }
    //最终将互斥锁解锁
    pthread_mutex_unlock(&myMutex);
    return NULL;
}
//线程执行的函数
//直到x == 10的时候，唤醒cond条件变量 pthread_cond_signal()
void * doneForTrue(void *args) {
    int res;

    while (x != 10) {
        //对互斥锁执行“加锁”操作
        res = pthread_mutex_lock(&myMutex);
        if (res == 0) {
            x++;
            printf("%lu doneForTrue：x = %d\n", pthread_self(), x );
            sleep(1);
            //对互斥锁“解锁”
            pthread_mutex_unlock(&myMutex);
        }
    }
    //发送“条件成立”的信号，解除 mythread1 线程的“被阻塞”状态
    res = pthread_cond_signal(&myCond);
    if (res != 0) {
        printf("解除阻塞失败\n");
    }
    return NULL;
}
int main() {
    int res;
    pthread_t mythread1, mythread2;
    res = pthread_create(&mythread1, NULL, waitForTrue, NULL);
    if (res != 0) {
        printf("mythread1线程创建失败\n");
        return 0;
    }
    res = pthread_create(&mythread2, NULL, doneForTrue, NULL);
    if (res != 0) {
        printf("mythread2线程创建失败\n");
        return 0;
    }
    //等待 mythread1 线程执行完成
    res = pthread_join(mythread1, NULL);
    if (res != 0) {
        printf("1：等待线程失败\n");
    }
    //等待 mythread2 线程执行完成
    res = pthread_join(mythread2, NULL);
    if (res != 0) {
        printf("2：等待线程失败\n");
    }
    //销毁条件变量
    pthread_cond_destroy(&myCond);
    return 0;

    /**
     * @brief result
     * 
     * 140171421927168 waitForTrue ---等待 x 的值为 10
        140171413534464 doneForTrue：x = 1
        140171413534464 doneForTrue：x = 2
        140171413534464 doneForTrue：x = 3
        140171413534464 doneForTrue：x = 4
        140171413534464 doneForTrue：x = 5
        140171413534464 doneForTrue：x = 6
        140171413534464 doneForTrue：x = 7
        140171413534464 doneForTrue：x = 8
        140171413534464 doneForTrue：x = 9
        140171413534464 doneForTrue：x = 10
        140171421927168 waitForTrue  x = 10
     * 
     * 
     */
}
