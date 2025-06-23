// 1.4把文件重定向到标准输出.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
int main()
{
    //打开一个文件， 用writefile写到标准输出(用std_output_handle)
    HANDLE fh = CreateFile(L"1.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fh == INVALID_HANDLE_VALUE) {
        std::cout << "文件打开出错了 " << std::endl;
        return 0;
    }
    unsigned long buff_size = GetFileSize(fh, 0);
    char* buff = new char[buff_size + 1];
    memset(buff, 0, buff_size + 1);//清0
    //写进缓存
    unsigned long swap_size;
    if (!ReadFile(fh, buff, buff_size, &swap_size, NULL)) {
        std::cout << "文件读进缓存出错" << std::endl;
        delete[] buff;
        CloseHandle(fh);
        return 0;
    }

    std::cout << "buff内容为:" << buff << std::endl;
    CloseHandle(fh);//关闭文件句柄


    unsigned long real_write_size;
    HANDLE console_output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console_output == INVALID_HANDLE_VALUE) {
        std::cout << "获取标准输出句柄失败" << std::endl;
        return 0;
    }
    WriteFile(
        console_output,
        buff,
        swap_size, //ReadFile读到的大小
        &real_write_size, //实际写入多少
        NULL);
    std::cout << std::endl;
    std::cout << "实际输出了:" << real_write_size << "字节" << std::endl;
    std::cout << "done" << std::endl;
    delete[] buff;
    
}