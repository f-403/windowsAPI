// 1.获取某个键的状态.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    //右移， 有符号的， 最位是1就补1， 是0就补0，无符号全补0
    //查看键盘状态， 只查看高位， 是1就是按下， 是0就是放开， 只查16位中的最高位
    //GetAsyncKeyState实时检测， 用这个就行了
    //GetKeyState是从消息队列中获取， 要窗口外于活动状态
    short state = (GetAsyncKeyState(VK_SHIFT) >> 15) & 1; 
    std::cout << state << std::endl;

}

