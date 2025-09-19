// 5.2.获取映射的名字并读写.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
int main()
{
    HANDLE f_map = OpenFileMappingA(FILE_MAP_ALL_ACCESS,NULL, "GZ0668");
    void* mem = MapViewOfFile(f_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    std::cout << (char*)mem << std::endl;
    ((CHAR*)mem)[0] = 'O';
}

