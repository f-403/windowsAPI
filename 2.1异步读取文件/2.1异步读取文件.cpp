// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

OVERLAPPED ov{};
HANDLE event = CreateEvent(NULL, TRUE, FALSE, NULL);
HANDLE f = CreateFile(L"1.txt", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
LARGE_INTEGER f_pointer{};//用于保存文件指针用， 如某个线程读完后， 设置位置用于下个线程从哪个位置读取
int main()
{
	f_pointer.QuadPart = 0;//初始化为0
	ov.hEvent = event;//设置信号
	ov.Offset = f_pointer.LowPart;
	ov.OffsetHigh = f_pointer.HighPart;
	DWORD add_bytes;//用于记录文件移动位置
	char data[100]{ 0 };
	DWORD read_bytes;
	ReadFile(f, data, GetFileSize(f, NULL), &read_bytes, &ov);//ov参数可控制读取位置， 如果没指定， 是从当前文件指针位置读
	//在异步中， 每次调用后， 要用GetOverlappedResult(hFile, &ov, &bytesWritten, TRUE)获得实际读取了多少字节
	//再更新f_pointer.QuadPart, 再用f_pointer来设置ov中的文件指针位置，下次读取时传入ov就行。
	std::cout << "之前 bytes_read:" << read_bytes << std::endl;
	GetOverlappedResult(f, &ov, &read_bytes, TRUE);
	std::cout << "之后 bytes_read:" << read_bytes << std::endl;
	std::cout << data << std::endl;
	//更新指针与ov结构
	f_pointer.QuadPart += read_bytes;
	ov.Offset = f_pointer.LowPart;
	ov.OffsetHigh = f_pointer.HighPart;


}

