#include <mutex>          // std::mutex
#include <chrono>         // std::chrono::seconds()
#include <iostream>
#include <thread>         // std::this_thread::get_id()
using namespace std;
int  n = 0;
std::mutex mtx;           // 定义一个 mutex 类对象，创建一个互斥锁

void threadFun() {
    while(n<10){
        //对互斥锁进行“加锁”
        mtx.lock();
        n++;
        cout << "ID" << std::this_thread::get_id() << " n = "<< n << endl;
        //对互斥锁进行“解锁”
        mtx.unlock();
        //暂停 1 秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    thread th1(threadFun);
    thread th2(threadFun);

    th1.join();
    th2.join();
    return 0;

    /**
     * @brief result
     * 
        ID139845419403008 n = 1
        ID139845411010304 n = 2
        ID139845419403008 n = 3
        ID139845411010304 n = 4
        ID139845419403008 n = 5
        ID139845411010304 n = 6
        ID139845419403008 n = 7
        ID139845411010304 n = 8
        ID139845419403008 n = 9
        ID139845411010304 n = 10
     * 
     */
}