// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>


int main()
{
    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale(""));
    const wchar_t*  name = L"你好";
    std::wcout << name << std::endl;
}

