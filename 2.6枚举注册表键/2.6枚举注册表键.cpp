// 2.6枚举注册表键.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
int main()
{
    // 打开已存在的键
    //LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\MyApp", 0, KEY_READ, &hKey);
    // 打开或创建键
    //LSTATUS status2 = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\MyApp", 0, NULL,REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    HKEY key;
    LSTATUS check = RegCreateKeyExW(HKEY_CURRENT_USER,L"CLSID",0,NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
    if (check == ERROR_SUCCESS) {
        std::wcout << L"打开成功" << std::endl;
        wchar_t name[MAX_PATH];
        DWORD name_size;
        RegEnumKeyExW(key, 0, name, &name_size, NULL, NULL, NULL, NULL);
        std::wcout << L"name:" << name  << L", name_size: "<< name_size << std::endl;
        std::wcout << L"-----------------------------" <<  std::endl;

    }


    //枚举根目录下的所有子键， 直接用RegEnumKeyExw即可
    HKEY root = HKEY_CURRENT_USER;
    {
        int index = 0;
        for (;;) {
            wchar_t name[MAX_PATH];
            DWORD name_size = MAX_PATH;
            LSTATUS check = RegEnumKeyExW(root, index, name, &name_size, NULL, NULL, NULL, NULL);
            if (check == ERROR_SUCCESS) {
                std::wcout << L"name:" << name << L", name_size: " << name_size << std::endl;
                std::wcout << L"-----------------------------" << std::endl;
                index++;
                continue;
            }
            break;
        }
    
    }
}

