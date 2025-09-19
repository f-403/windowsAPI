// 创建进程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    
    STARTUPINFO si2{};
    si2.cb = sizeof(si2);
    PROCESS_INFORMATION pi2{};
    WCHAR app[] = L"C:\\Windows\\System32\\notepad.exe";//
    std::cout << CreateProcessW(app, NULL, NULL, NULL, FALSE,CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2) << std::endl;
    std::cout << GetLastError() << std::endl;
    WaitForSingleObject(pi2.hProcess, INFINITE);

    STARTUPINFO si{};//不一定要设置si.cb为结构大小， 这个大小会影响窗口标题，重定向之类的效果
    PROCESS_INFORMATION pi;
    //si.lpTitle = (LPWSTR)L"标题";

    
    //ZeroMemory(&pi, sizeof(pi));
    WCHAR cmd[] = L"CMD.EXE";
    std::cout << CreateProcessW(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    ) << std::endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << GetLastError() << std::endl;

 

}
