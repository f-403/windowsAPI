// 2.WINDOWS类型.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    //SetConsoleCP(CP_UTF8);//设置编码
    //SetConsoleOutputCP(CP_UTF8);
    LPCWSTR  test = L"高州";
    //std::wcout << test << std::endl;
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),test,wcslen(test),0,NULL);
}

