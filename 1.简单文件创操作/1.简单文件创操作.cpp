#include <windows.h>
#include <iostream>
int main() {
	
	/*
	INVALID_HANDLE_VALUE
	通常用于文件、管道等操作的返回值（如 CreateFile）。

	NULL
	其他内核对象（如线程、互斥量）的无效句柄可能直接返回 NULL。
	*/
	HANDLE f_handle = CreateFile(
		L"test.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		0,
		NULL);
	std::cout << f_handle << std::endl;
	if (f_handle == INVALID_HANDLE_VALUE) {
		std::cout << GetLastError() << std::endl;
		std::cout << "文件打开失败" << std::endl;
	}
}