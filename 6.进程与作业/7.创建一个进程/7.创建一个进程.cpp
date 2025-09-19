// 7.创建一个进程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    
    PROCESS_INFORMATION pi{};
    STARTUPINFO si{}; //与窗口相关
    si.cb = sizeof(si);
    //WCHAR app[] = L"C:\\Windows\\System32\\cmd.exe /k ipconfig";
    //CreateProcessW(NULL,app, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    //WaitForSingleObject(pi.hProcess, -1);

    WCHAR app[] = L"C:\\Windows\\System32\\cmd.exe";
    
    WCHAR cmdline[] = L"/c ipconfig";

    CreateProcessW(app,cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    //当第一个参数为NULL时， 第二个参数会折分出程序名+参数
    //当第一个参数不为NULL时， 第二个参数是传递到程序的参数，所以一般只写第二个参数就行了，第一个参数留空。
    //return 0;
    STARTUPINFO si2{};//不一定要设置si.cb为结构大小， 这个大小会影响窗口标题，重定向之类的效果
    PROCESS_INFORMATION pi2;//与窗口相关
    si2.lpTitle = (LPWSTR)L"标题";


    //ZeroMemory(&pi2, sizeof(pi2));
    WCHAR cmd[] = L"cmd.exe /k ipconfig";
    std::cout << CreateProcessW(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si2,
        &pi2
    ) << std::endl;
    WaitForSingleObject(pi2.hProcess, INFINITE);
    std::cout << GetLastError() << std::endl;
    CloseHandle(pi2.hProcess);
}

