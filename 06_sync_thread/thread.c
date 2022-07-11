#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>  // -- sleep()

//全局变量，模拟总的票数
int ticket_sum = 10;
//模拟4个售票员一起售卖票的过程
void *sell_ticket(void *arg){
    int i;
    //4个售票员负责将 10 张票全部卖出
    for (i = 0; i < 10; i++)
    {
        //直至所有票全部卖出，4 个售票员才算完成任务
        if (ticket_sum > 0)
        {
            sleep(1);
            //每个线程代表一个售票员
            printf("%lu 卖第 %d 张票\n", pthread_self(), 10 - ticket_sum + 1);
            ticket_sum--;
        }
    }
    return 0;
}

int main(){
    int flag;
    int i;
    void *ans;
    //创建 4 个线程，代表 4 个售票员
    pthread_t tids[4];
    for (i = 0; i < 4; i++)
    {
        flag = pthread_create(&tids[i], NULL, &sell_ticket, NULL);
        if (flag != 0) {
            printf("线程创建失败!");
            return 0;
        }
    }
    sleep(10); // 阻塞主线程，等待所有子线程执行结束
    for (i = 0; i < 4; i++)
    {
        flag = pthread_join(tids[i], &ans);
        if (flag != 0) {
            printf("tid=%ld 等待失败！", tids[i]);
            return 0;
        }
    }
    return 0;

    /**
     * @brief 
     * 多个线程同时访问某一公共资源”的现象称为“线程间产生了资源竞争”或者“线程间抢夺公共资源”，
     * 线程间竞争资源往往会导致程序的运行结果出现异常，感到匪夷所思，严重时还会导致程序运行崩
     *  140200911886080 卖第 1 张票
        140200886707968 卖第 1 张票
        140200895100672 卖第 1 张票
        140200903493376 卖第 1 张票
        140200911886080 卖第 5 张票
        140200886707968 卖第 6 张票
        140200895100672 卖第 7 张票
        140200903493376 卖第 8 张票
        140200911886080 卖第 9 张票
        140200886707968 卖第 10 张票
        140200895100672 卖第 11 张票
        140200903493376 卖第 12 张票
        140200911886080 卖第 13 张票
     * 
     */
}