#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

void threadFun1(int n) {
    sleep(5);
    cout << "---thread1 running\n";
    cout << "n=" << n << endl;
}

void threadFun2(const char * url) {
    cout << "---thread2 running\n";
    cout << "url=" << url << endl;
}

int main() {
    //调用第 1 种构造函数
    thread thread1(threadFun1, 10);
    //输出 thread1 线程的 ID
    cout << "thread1 ID:" << thread1.get_id() << endl;
    //调用移动构造函数
    thread thread2 = std::thread(threadFun2, "http://c.biancheng.net");
    //输出 thread2 线程的 ID
    cout << "thread2 ID:" << thread2.get_id() << endl;
    //将 thread1 与主线程分离开，thread1 线程独立执行。
    thread1.detach();
    //判断 thread2 线程是否可以调用 join() 函数
    if (thread2.joinable()) {
        //阻塞主线程，直至 thread2 线程执行完毕。
        thread2.join();
    }
    cout << "main finished" << endl;
    return 0;
    /**
     * @brief result
     * 
     * thread1 线程执行结果并没有显示到屏幕上
     * 这是因为 thread1 线程还未执行输出语句，主线程就已经执行结束（整个进程也执行结束），thread1 线程无法将执行结果输出到屏幕上
        thread1 ID:140040366036736
        thread2 ID:140040357644032
        ---thread2 running
        url=http://c.biancheng.net
        main finished
     * 
     */
}