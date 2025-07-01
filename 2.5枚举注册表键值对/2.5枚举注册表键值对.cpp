// 2.5枚举注册表键值对.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    //先打注册表
    HKEY key;
    LSTATUS check = RegCreateKeyExW(HKEY_CURRENT_USER,L"AAAAA\\abc\\",0,NULL,0L,KEY_ALL_ACCESS,NULL,&key,NULL);
    if (check == ERROR_SUCCESS) {
        std::cout << "打开成功" << std::endl;
        //RegCloseKey(key);


        //枚举子键
        std::wcout << L"找到的键如下:" << std::endl;
        DWORD kname_size = MAX_PATH;
        wchar_t kname[MAX_PATH];
        LSTATUS key_check =  RegEnumKeyExW(key,0,kname,&kname_size, NULL, NULL, NULL, NULL);
        if (key_check == ERROR_SUCCESS) {
            std::wcout << L"name:" << kname << std::endl;
            std::wcout << L"name_size:" << kname_size << std::endl;
            /*
                打开成功
                name:NetProbe
                name_size:8
            */
        }
        else
        {
            std::cout << "枚举失败" << std::endl;
        }
        RegCloseKey(key);

        int index = 0;
        for (;;) {
            std::wcout << L"键值对如下:" << std::endl;
            //枚举子键下的键值对
            //打开新的KEY
            RegCreateKeyExW(HKEY_CURRENT_USER, L"BILIBILI", 0, NULL, 0L, KEY_ALL_ACCESS, NULL, &key, NULL);
            DWORD  kname_keyname_size = MAX_PATH;
            wchar_t kname_keyname[MAX_PATH];
            DWORD  kname_keyvalue_size = MAX_PATH;
            wchar_t kname_keyvalue[MAX_PATH];
            LSTATUS key_value_check = RegEnumValueW(key, index, kname_keyname, &kname_keyname_size, NULL, NULL, reinterpret_cast<BYTE*>(kname_keyvalue), &kname_keyvalue_size);
            if (key_value_check == ERROR_SUCCESS) {
                std::wcout << L"---------------------------------------------------" << std::endl;
                std::wcout << L"kname_keyname:" << kname_keyname << std::endl;
                std::wcout << L"kname_kname_size:" << kname_keyname_size << std::endl;
                std::wcout << L"kname_keyvalue:" << kname_keyvalue << std::endl;
                std::wcout << L"kname_keyvalue_size:" << kname_keyvalue_size << std::endl;
                std::wcout << L"---------------------------------------------------" << std::endl;
                /*
                *   打开成功
                    找到的键如下:
                    name:NetProbe
                    name_size:8
                    键值对如下:
                    ---------------------------------------------------
                    kname_keyname:name
                    kname_kname_size:4
                    kname_keyvalue:高州
                    kname_keyvalue_size:6
                    ---------------------------------------------------
                    键值对如下:
                    ---------------------------------------------------
                    kname_keyname:this is a test
                    kname_kname_size:14
                    kname_keyvalue:flag for it
                    kname_keyvalue_size:24
                    ---------------------------------------------------
                    键值对如下:
                    枚举键值对失败
                */
            }
            else
            {
                std::cout << "枚举键值对失败(准备跳出循环)" << std::endl;
                break;
            }
            index++;
        }
    }
}
/*

 HKEY_CURRENT_USER
└── Software
    └── 360Safe
        └── 360Scan
            └── NetProbe
                ├── 键值对（如：Version = "1.0"）
                └── 子键（可能还有，例如 Config）

*/


