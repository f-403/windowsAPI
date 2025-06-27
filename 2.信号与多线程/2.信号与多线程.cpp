// 2.信号与多线程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <Windows.h>

void print_ascii();
void print_numbers();
void print_message();
//创建一个信号
HANDLE event = CreateEvent(NULL, FALSE, FALSE, NULL);//自动重置
int main()
{
    std::cout << "线程启动" << std::endl;
    std::thread t(print_ascii);
    std::thread t2(print_numbers);
    std::thread t3(print_message);
    t.join();
    t2.join();
    t3.join();
    std::cout << "线程执行完成" << std::endl;
    
}
void print_ascii() {
    for (int i = 65; i < 75; i++) {
        std::cout << "ascii = " << char(i) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //SetEvent(event);
    }
    std::cout << "print_ascii已执行完，发送信号让print_message启动" << std::endl;
    //SetEvent(event);
}

void print_numbers() {
    for (int i = 0; i < 10; i++) {
        std::cout << "i = " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void print_message() {
    //WaitForSingleObject(event, INFINITE);//一直阻塞
    WaitForSingleObject(event, 2000);//只等待2秒
    for (int i = 0; i < 10; i++)
    {
        std::cout << "我收到了信号，正在打印: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
