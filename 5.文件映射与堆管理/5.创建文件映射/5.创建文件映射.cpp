// 5.创建文件映射.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    HANDLE f = CreateFileA("1.txt", GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    //创建文件映射
    HANDLE fmap = CreateFileMapping(f, NULL, PAGE_EXECUTE_READWRITE, 0,0,NULL);
    if (fmap == NULL) {
        std::cout << "文件映射失败" << std::endl;
        return 0;
    }

    void* file_in_mem = MapViewOfFile(fmap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    std::cout << (char*)file_in_mem << std::endl;

    DWORD f_max = GetFileSize(f, NULL);
    std::cout << f_max << std::endl;

    for (int i = 0; i < f_max; i++) {
        std::cout << ((char*)file_in_mem)[i] << std::endl;
        if (i == 2) {
            ((char*)file_in_mem)[i] = 'A';
        }
    }

    FlushViewOfFile(file_in_mem, 0);
    UnmapViewOfFile(file_in_mem);
    CloseHandle(fmap);
    CloseHandle(f);


}

