// 5.2设置映射名字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
int main()
{
    HANDLE f = CreateFileA("1.txt", GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE f_map = CreateFileMappingA(f, NULL, PAGE_EXECUTE_READWRITE, 0, 0, "GZ0668");

    void* mem = MapViewOfFile(f_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    std::cout << (char*)mem << std::endl;
    system("pause");
    std::cout << (char*)mem << std::endl;
    system("pause");
}

