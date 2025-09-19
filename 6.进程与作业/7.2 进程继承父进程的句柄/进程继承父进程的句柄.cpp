// 进程继承父进程的句柄.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <string>
int main()
{
    SECURITY_ATTRIBUTES sa{};
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(sa);
    HANDLE f = CreateFileA("1.TXT", GENERIC_ALL, 0, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    PROCESS_INFORMATION pf{};
    STARTUPINFO st{};
    st.cb = sizeof(st);
    std::wstring cmd = L"1.exe " + std::to_wstring((uintptr_t)f);
    std::cout << "当前句柄值为:" << f << std::endl;
    int check = CreateProcess(NULL, &cmd[0], NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &st, &pf);
    if (check == FALSE) {
        std::cout << "调用失败" << std::endl;
        return 0;
    }
    //带W版本能传常量， A版本要用char []可修改的数组形式

    WaitForSingleObject(pf.hProcess, -1);


}


