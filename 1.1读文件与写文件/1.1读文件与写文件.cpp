// 1.1读文件与写文件.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <vector>

int main()
{
    HANDLE f_h = CreateFile(
        L"text.txt",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_ALWAYS,
        0,
        NULL);
    if (f_h == INVALID_HANDLE_VALUE) {
        std::cout << "FIle open error" << std::endl;
        return 0;
    }

    //写
    std::string data = "荔枝收获季节你好"; //std::wstring data = L"A" -->字符数data.length()
    unsigned long number_of_bytes_write{};
    int check = WriteFile(
        f_h,
        data.c_str(),
        data.length(),//这里是字节， 注意如果是wchar_t类型的， 先计算字符数再乘以sizeof(wchar_t)
        &number_of_bytes_write,//读入了多少字节
        NULL);
    if (check) {
        std::cout << "写入成功，写入了:" << number_of_bytes_write << " 字节" << std::endl;
        std::cout << "data.length():" << data.length() << " 字节" << std::endl;
        
        
        
    }



}

