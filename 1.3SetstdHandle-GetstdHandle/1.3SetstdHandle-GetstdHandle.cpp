// 1.3SetstdHandle-GetstdHandle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
int main()
{
    HANDLE f_handle = CreateFileW(
        L"test.txt",
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (f_handle == INVALID_HANDLE_VALUE) {
        std::cout << "文件创建失败" << std::endl;
        return 0;
    }
    int check = SetStdHandle(STD_OUTPUT_HANDLE, f_handle); //重定向,// 设置标准输出句柄（仅影响 WriteConsole/WriteFile）
    if (check == 0) {
        std::cout << "重定向失败" << std::endl;
        return 0;
    }
    // 设置标准输出句柄（仅影响 WriteConsole/WriteFile）
    std::cout << "这是一个测试\n"; //不会输出到文件
    printf("this is a test\n"); //不会输出到文件
    CloseHandle(f_handle);
    //可以用另一种方法
    FILE* fp;
    freopen_s(&fp, "1.txt", "wb+", stdout); //fp会与文件名1.txt关联
    std::cout << "test" << std::endl;
    printf("你好\n");
    fclose(fp);

    
}

