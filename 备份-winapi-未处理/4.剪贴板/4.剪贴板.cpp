// 4.剪贴板.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
int main()
{
	//堆分配内存
    HGLOBAL glom = GlobalAlloc(GHND, 1024);
	if (glom==NULL)
	{
		std::cout << "分配失败" << std::endl;
		return 0;
	}
	//重新调节分配大小 // 注意：使用GlobalReAlloc后应使用新句柄，原句柄已无效
	HGLOBAL glom2 = GlobalReAlloc(glom, 2048, GMEM_ZEROINIT);
	if (glom2 == NULL)
	{
		std::cout << "分配失败" << std::endl;
		return 0;
	}
	//获取大小
	SIZE_T glom_size2 = GlobalSize(glom2);
	std::cout << " glom_size2 = " << glom_size2<< std::endl;

	//锁定
	int *p = (int*)GlobalLock(glom2);
	if (p == NULL) {
		std::cout << "锁定失败" << std::endl;
		GlobalFree(glom2);
		return 0;
	}
	*p = 12343;
	std::cout << *p << std::endl;

	std::cout << glom2 << std::endl;
	std::cout << p << std::endl;


	//解锁
	int check = GlobalUnlock(glom2);
	if (check == 0) {
		//std::cout << "解锁失败" << std::endl;
		std::cout << GetLastError() << std::endl;
		DWORD err = GetLastError();
		if (err != NO_ERROR)  // 只有 GetLastError() 返回非零才算真正的失败
		{
			std::cout << "解锁失败，错误代码: " << err << std::endl;
		}
		
	}
	//释放内存
	GlobalFree(glom2);
	

	return 0;
}
