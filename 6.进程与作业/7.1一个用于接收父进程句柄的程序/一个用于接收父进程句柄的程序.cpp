#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[]) {


	if (argc < 2) {
		std::cerr << "use: 程序.exe 句柄" << std::endl;
		system("pause");
		return 0;
	}
	//利用标准C函数读取参数
	char* check_char = nullptr;
	errno = 0;//初始化内置变量
	ULONGLONG get_ulonglong = strtoull(argv[1], &check_char, 0);
	//数字转指针再转为HANDLE
	HANDLE get_h = HANDLE( uintptr_t(get_ulonglong));
	
	if (errno == ERANGE) {
		std::cout << "转换出错" << std::endl;
		system("pause");
		return 0;
	}
	if (*check_char != '\0') {
		std::cout << "含有字符， 转换可能不正确" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "获取到的句柄为: " << std::hex << get_h<< std::endl;
	//写数据
	DWORD write_bytes{};
	WriteFile(get_h, u8"这是子进程写入的数据",strlen(u8"这是子进程写入的数据"),&write_bytes,NULL);//注意编码
	//strlen返回字节数， 不含9， 而sizeof含0
	//const wchar_t* wdata = L"这是子进程写入的数据";
	//DWORD bytesToWrite = (DWORD)(wcslen(wdata) * sizeof(wchar_t)); // 宽字符字节数
	//
	std::cout << "写入了:" << write_bytes << " 字节" << std::endl;

	system("pause");
	return 0;
}
/*
1️⃣ strtoull 的作用
ULONGLONG get_ulonglong = strtoull(argv[1], &check_char, 0);


argv[1] 是命令行传进来的字符串，比如 "12345"。

strtoull 会尝试把字符串转换成 unsigned long long（这里是 ULONGLONG）。

&check_char 是一个 输出参数，函数会把第一个 无法转换的字符的位置 存到 check_char。

例如：

const char* str = "123abc";
char* endptr;
unsigned long long val = strtoull(str, &endptr, 0);


val = 123

endptr 指向 "a"，也就是 "abc" 的开头。

2️⃣ 检查 *check_char != '\0'
if (*check_char != '\0') {
	std::cout << "含有字符， 转换可能不正确" << std::endl;
}


*check_char 是 check_char 指针指向的字符。

如果转换成功且整个字符串都是数字，那么 check_char 会指向字符串末尾的 '\0'（C 字符串结尾标志）。

如果 *check_char != '\0'，说明字符串中 有非数字字符，转换不完全。

举例：

argv[1] = "12345";
strtoull(argv[1], &check_char, 0);
// check_char 指向 '\0'
// *check_char == '\0' → OK

argv[1] = "123abc";
strtoull(argv[1], &check_char, 0);
// check_char 指向 'a'
// *check_char != '\0' → 输入有非数字


✅ 总结：
*check_char != '\0' 是用来检测 输入字符串是否完全由数字组成。如果不是，就提示转换可能不正确。

*/