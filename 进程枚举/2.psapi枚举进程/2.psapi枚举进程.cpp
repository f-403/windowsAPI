// 2.psapi枚举进程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")//要使用EnumProcessModules要引入库
int main()
{
    //导入一只dll做测试,下面会查找到的
    //LoadLibrary(LR"(C:\Users\who\Desktop\test\dll\x64\Debug\DLL.DLL)");

    std::cout << GetCurrentProcessId() << std::endl;//获取当前进程ID
    //std::cout << GetCurrentProcessToken() << std::endl;

    //获取所有进程ID
    DWORD allprocessid[2048], real_id_number_write;
    if (!EnumProcesses(allprocessid, sizeof(allprocessid), &real_id_number_write)) {
        std::cout << "获取失败" << std::endl;
        return 0;
    }
    std::cout << "实际进程ID数量：" << real_id_number_write/sizeof(DWORD) << std::endl;
    //实际返回的进程数量 == 你提供的数组能容纳的最大进程数量， 说明有可能被截断了， 最好数组还要给大一些

    //列出所有ID
    for (int i = 0; i < real_id_number_write / sizeof(DWORD); i++) {
        std::wcout << L"ID:" << allprocessid[i] << std::endl;
    }

    //打开进程， 不要测试太高权限：PROCESS_ALL_ACCESS， 最后用最低权限打开， 否则检测会失败
    //PROCESS_QUERY_INFORMATION | PROCESS_VM_READ， 文档有说各种权限标志
    HANDLE processid_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    if (!processid_handle) {
        std::cout << "测试打开进程成败" << std::endl;
        return 0;
    }

    //打开进程后， 就能获取里面的信息了
    //一个进程 = 主程序（EXE） + 它依赖的所有 DLL
    HMODULE enumprocess_handle[1024];
    DWORD real_enumprocess_handle_write;
    if (!EnumProcessModules(processid_handle, enumprocess_handle, sizeof(enumprocess_handle), &real_enumprocess_handle_write)) {
        std::cout << "获取指定进程的模块失败" << std::endl;
        return 0;
    }
    std::cout << "指定进程中的模块数量为:" << real_enumprocess_handle_write / sizeof(HMODULE) << std::endl;
    //注意， 这里没有判断数组是否足够大， 你要对比real_enumprocess_handle_write / sizeof(HMODULE)与1024数组大小

    //用GetModuleBaseName获取模块信息
    int max_module = real_enumprocess_handle_write / sizeof(HMODULE);
    WCHAR basename[MAX_PATH + 1]{};
    for (int i= 0; i < max_module; i++) {
        DWORD c = GetModuleBaseName(processid_handle, enumprocess_handle[i], basename, MAX_PATH);
        //GetModuleBaseName返回实际写入字节数， 当函数返回时， 可以检测它的返回值是否能真正获取到模块名
        if (c > 0) {
            wprintf(L"NAME:%s\n", basename);
            /*
            NAME:2.psapi????.exe
            NAME:ntdll.dll
            NAME:KERNEL32.DLL
            NAME:KERNELBASE.dll
            NAME:MSVCP140D.dll
            NAME:VCRUNTIME140_1D.dll
            NAME:VCRUNTIME140D.dll
            NAME:ucrtbased.dll
            */
        }
        else {
            wprintf(L"没有获取到模块名字\n");
        }
    }
    

}   

