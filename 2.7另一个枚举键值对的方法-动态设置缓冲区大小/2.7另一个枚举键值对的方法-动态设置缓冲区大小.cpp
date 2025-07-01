// 2.5枚举注册表键值对.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <vector>
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    //先打注册表
    HKEY key;
    LSTATUS check = RegCreateKeyExW(HKEY_CURRENT_USER, L"AAAAA\\1234567890\\", 0, NULL, 0L, KEY_ALL_ACCESS, NULL, &key, NULL);
    if (check == ERROR_SUCCESS) {
        std::cout << "打开成功" << std::endl;
        //RegCloseKey(key);
        DWORD value_name_length, value_length;
        RegQueryInfoKeyW(key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &value_name_length, &value_length, NULL, NULL);

        std::wcout << L"value_name_length:" << value_name_length << std::endl;
        std::wcout << L"value_lehgth:" << value_length << std::endl;
        //return 0;
        int index = 0;
        for (;;) {
            DWORD check_type;
            DWORD current_value_name_length = value_name_length + 1;
            DWORD current_value_length = value_length + sizeof(WCHAR);
            std::vector<WCHAR>value(current_value_length);
            std::vector<WCHAR>value_name(current_value_name_length);
            LSTATUS c = RegEnumValue(key, index, value_name.data(), &current_value_name_length, NULL, &check_type, (byte*)(value.data()), &current_value_length);
            if (c == ERROR_SUCCESS) {
                std::wcout << L"获取到的值名字是:" << value_name.data() << L",值名长度为:" << current_value_name_length << std::endl;
                std::wcout << L"获取到的值是:" << value.data() << L",值长度为(字节):" << current_value_length << std::endl;
                std::wcout << L"获取到的值类型为:" << check_type << std::endl;
                //REG_SZ
                index++;
                continue;
            }
            else {
                std::wcout << L"没有更多数据可用" << std::endl;
                break;
            }
        }

    }
    RegCloseKey(key);
}




