#include <iostream>
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable_any
#include <chrono>         // std::chrono::seconds()
//创建一个互斥锁
std::mutex mtx;
//创建一个条件变量
std::condition_variable_any cond;

void print_id() {
    mtx.lock();
    //阻塞线程，直至条件成立
    cond.wait(mtx);
    std::cout << "----threadID " << std::this_thread::get_id() <<" run" << std::endl;
    //等待 2 秒
    std::this_thread::sleep_for(std::chrono::seconds(2));
    mtx.unlock();
}

void go() {
    std::cout << "---threadID "<<std::this_thread::get_id()<<" go running\n";
    //阻塞线程 2 秒钟
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //通知所有等待的线程条件成立
    cond.notify_all();
}

int main()
{
    //创建 4 个线程执行 print_id() 函数
    std::thread threads[4];
    for (int i = 0; i < 4; ++i)
        threads[i] = std::thread(print_id);
    //创建 1 个线程执行 go() 函数
    std::thread goThread(go);
    //等待所有线程执行结果后，主线程才能继续执行
    goThread.join();
    for (auto& th : threads) {
        th.join();
    }
    return 0;
    /**
     * @brief result
     * 
        ---threadID 139827656726272 go running
        ----threadID 139827690297088 run
        ----threadID 139827665118976 run
        ----threadID 139827681904384 run
        ----threadID 139827673511680 run
     * 
     */
}