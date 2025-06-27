#include <iostream>
#include <Windows.h>

int main() {
	HKEY key;
	LSTATUS check = RegCreateKeyExW(HKEY_CURRENT_USER, L"BILIBILI", 0, NULL, 0L, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (check == ERROR_SUCCESS) {
		std::cout << "创建成功" << std::endl;
		//RegCloseKey(key);

		//写入一个name, 值为gz
		const wchar_t* name = L"name";
		const wchar_t* value = L"高州";
		check = RegSetValueEx(key, name, 0, REG_SZ, reinterpret_cast<CONST BYTE*>(value), wcslen(value) * sizeof(wchar_t));
		if (check == ERROR_SUCCESS) {
			std::cout << "写入键值对成功" << std::endl;
		}
	}

	//一个写进二进制的例子
	{
		BYTE myData[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
		DWORD myDataSize = sizeof(myData);
		LSTATUS check = RegCreateKeyExW(HKEY_CURRENT_USER, L"BILIBILI", 0, NULL, 0L, KEY_ALL_ACCESS, NULL, &key, NULL);
		LSTATUS status = RegSetValueExW(
			key,
			L"MyBinaryValue",
			0,
			REG_BINARY,
			myData,
			myDataSize
		);

		if (status == ERROR_SUCCESS) {
			std::wcout << "写入二进制数据成功！" << std::endl;
		}
		else {
			std::wcerr << "写入失败，错误码：" << status << std::endl;
		}
	
	}





}