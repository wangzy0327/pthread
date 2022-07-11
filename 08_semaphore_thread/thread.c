#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>   // sem_t
#include<unistd.h>
//创建信号量
sem_t mySem;
//设置总票数
int ticket_sum = 10;
//模拟买票过程
void *sell_ticket(void *arg) {
    printf("当前线程ID：%lu\n", pthread_self());
    int i;
    int flag;
    for (i = 0; i < 10; i++)
    {
        //完成信号量"减 1"操作，否则暂停执行
        flag = sem_wait(&mySem);
        if (flag == 0) {
            if (ticket_sum > 0)
            {
                sleep(1);
                printf("%lu 卖第 %d 张票\n", pthread_self(), 10 - ticket_sum + 1);
                ticket_sum--;
            }
            //执行“加1”操作
            sem_post(&mySem);
            sleep(1);
        }
    }
    return 0;
}


void business_ticket(){
    int flag;
    int i;
    void *ans;
    //创建 4 个线程
    pthread_t tids[4];
    //初始化信号量
    flag = sem_init(&mySem, 0, 1);
    if (flag != 0) {
        printf("初始化信号量失败\n");
    }
    for (i = 0; i < 4; i++)
    {
        flag = pthread_create(&tids[i], NULL, &sell_ticket, NULL);
        if (flag != 0) {
            printf("线程创建失败!");
            return ;
        }
    }
    sleep(10);
    for (i = 0; i < 4; i++)
    {
        flag = pthread_join(tids[i], &ans);
        if (flag != 0) {
            printf("tid=%ld 等待失败！", tids[i]);
            return ;
        }
    }
    //执行结束前，销毁信号量
    sem_destroy(&mySem);
    /**
     * @brief 二进制信号量
     * 
     * 当前线程ID：140290244904704
        当前线程ID：140290219726592
        当前线程ID：140290228119296
        当前线程ID：140290236512000
        140290244904704 卖第 1 张票
        140290219726592 卖第 2 张票
        140290228119296 卖第 3 张票
        140290236512000 卖第 4 张票
        140290244904704 卖第 5 张票
        140290219726592 卖第 6 张票
        140290228119296 卖第 7 张票
        140290236512000 卖第 8 张票
        140290244904704 卖第 9 张票
        140290219726592 卖第 10 张票
     * 
     */
}

//设置办理业务的人数
int num = 5;

//模拟办理业务的过程
void *get_service(void *arg)
{
    int id = *((int*)arg);
    //信号量成功“减 1”后才能继续执行
    //set_wait 信号量不为0是,返回0 信号量为0时，阻塞，返回非0
    if (sem_wait(&mySem) == 0)
    {
        printf("---customer%d 正在办理业务\n", id);
        sleep(2);
        printf("---customer%d 已办完业务\n", id);
        //信号量“加 1”
        sem_post(&mySem);
    }
    return 0;
}

void business_bank(){
    int flag,i,j;
    //创建 5 个线程代表 5 个人
    pthread_t customer[5];
    //初始化信号量
    sem_init(&mySem, 0, 2);
    for (i = 0; i < num; i++)
    {
        flag = pthread_create(&customer[i], NULL, get_service, &i);
        if (flag != 0)
        {
            printf("线程创建失败!\n");
            return ;
        }
        else {
            printf("customer%d 来办理业务\n",i);
        }
        sleep(1);
    }
    for (j = 0; j < num; j++)
    {
        flag = pthread_join(customer[j], NULL);
        if (flag != 0) {
            printf("tid=%ld 等待失败！", customer[i]);
            return ;
        }
    }
    sem_destroy(&mySem);
    /**
     * @brief  计数信号量
     * 
     * customer0 来办理业务
        ---customer0 正在办理业务
        customer1 来办理业务
        ---customer1 正在办理业务
        ---customer0 已办完业务
        customer2 来办理业务
        ---customer2 正在办理业务
        ---customer1 已办完业务
        customer3 来办理业务
        ---customer3 正在办理业务
        ---customer2 已办完业务
        customer4 来办理业务
        ---customer4 正在办理业务
        ---customer3 已办完业务
        ---customer4 已办完业务
     * 
     */
}

int main() {
    business_ticket();
    // business_bank();
    return 0;
}