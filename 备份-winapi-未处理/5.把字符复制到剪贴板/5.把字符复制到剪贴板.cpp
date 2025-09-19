// 5.把字符复制到剪贴板.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

/*

关于内存接管

1.当你 OpenClipboard()
仅获得剪贴板的操作权限
不会接管任何内存所有权
此时仍需手动管理 GlobalAlloc 分配的内存

2. 当你 SetClipboardData()
成功调用后，系统自动接管传入的 HGLOBAL 内存
从此刻起，禁止对该内存调用 GlobalFree
如果调用失败（返回 NULL），仍需手动释放内存
*/


int main() {
	std::string name = "this is a tes11111111t";

	GLOBALHANDLE gh = GlobalAlloc(GHND, name.size()+1);
	//写入之前锁定
	char *d = (char*)GlobalLock(gh);
	memcpy(d, name.c_str(), name.size());
	d[name.size()] = '\0';
	std::cout << d << std::endl;
	GlobalUnlock(gh);

	//打开剪贴板
	OpenClipboard(NULL);//打开
	EmptyClipboard();//清空

	SetClipboardData(CF_TEXT, d);//写入
	//CF_TEXT常量有多种类型
	//从新清空，
	//EmptyClipboard();
	CloseClipboard(); //关闭
	//GlobalFree(gh);剪贴板现在拥有了gh, 这里不要释讨

	//下面重新打开剪贴板读取数据并提取出来
	//--------------------------------------------------------------------------
	
	//从剪贴板提取txt
	if (!IsClipboardFormatAvailable(CF_TEXT)) {
		std::cout << "剪贴板没有内容" << std::endl;
	}
	std::string data;
	HANDLE hm = GetClipboardData(CF_TEXT);  //CF_UNICODETEXT为unicode的内容
	char* data_swap = (char*)GlobalLock(gh);
	data = data_swap;
	GlobalUnlock(gh);
	CloseClipboard();

	std::cout << "剪贴板内容: " << data << std::endl;
}