// 1.ToolHelp32 快照 API 枚举进程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <Windows.h>
#include <tlhelp32.h>//放在win下面， 要不没有提示ctrl+j
#include <WinBase.h> //用于字符串比较函数
int main()
{
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (h == INVALID_HANDLE_VALUE) {
        std::cout << "生成快照失败" << std::endl;
        return 0;
    }
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32FirstW(h, &pe)) {
        do {
            std::wcout << L"id:" << pe.th32ProcessID  << L"\tname:"<<  pe.szExeFile << std::endl;
            if (!lstrcmpiW(pe.szExeFile, L"svchost.exe")) {
                std::cout << "FOUND" << std::endl;
                //return 0;
            }
        } while (Process32NextW(h, &pe));
    }

}

