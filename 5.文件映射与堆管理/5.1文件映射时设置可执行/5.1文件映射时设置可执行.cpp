// 5.1文件映射时设置可执行.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE f = CreateFileA("1.txt", GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD f_size = GetFileSize(f, NULL);

	HANDLE f_map = CreateFileMappingW(f, NULL, PAGE_EXECUTE_READWRITE, 0, 0, NULL);
	void* mem = MapViewOfFile(f_map,FILE_MAP_ALL_ACCESS|FILE_MAP_EXECUTE, 0, 0, 0);
	//执行

	for (int i = 0; i < f_size; i++) {
		std::cout << std::hex << (int)((unsigned char*)mem)[i] << " ";
	}

	((void(*)()) mem) ();

}

