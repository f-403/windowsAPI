// TEST1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <vector>
int main()
{
    /*
    //以字符数为单位， 不是字节
    const int size = 1;
    const wchar_t* name = L"测试";
    wchar_t buff[size];
    DWORD mode;
    std::cout << GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode); //获取当前模式
    std::cout << "modde:" << mode << std::endl;
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), name, wcslen(name), NULL, NULL);
    DWORD read_world;
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buff, size,&read_world, NULL);//最多读取size大小， 读入的字符数存在read_world里
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buff, read_world, NULL, NULL);//读出来
    */

    CreateDirectory(TEXT("ABC"), NULL);
    RemoveDirectory(TEXT("ABC"));
    wchar_t dir[100];

    DWORD check = GetCurrentDirectory(100, dir); //第一个参数为缓冲区长度， 以TCHAR为单位
    //如果 lpBuffer 指向的缓冲区不够大，则返回值以字符为单位指定缓冲区的所需大小，包括 null 终止符。
    //失败返回0


    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale("")); //如果下面是用writeconsole打印的话，这两句可以不要

    std::cout << "check:" << check << "个字符" << std::endl;
    std::wcout << dir << std::endl;
}

