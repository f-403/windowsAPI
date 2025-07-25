﻿#include <iostream>
#include <Windows.h>
#include <winternl.h> //用于NetQuerySysteminfo结构
#include <vector>

/*
*           //系统已有
* 
typedef enum _SYSTEM_INFORMATION_CLASS {  
    SystemBasicInformation = 0,          // 获取系统基础信息
    SystemProcessorInformation = 1,      // 获取处理器相关信息
    SystemPerformanceInformation = 2,    // 获取性能统计信息
    SystemTimeOfDayInformation = 3,      // 获取系统当前时间和启动时间等
    SystemProcessInformation = 5,        // 获取系统进程信息（含线程）
    SystemProcessorPerformanceInformation = 8, // 每个处理器的性能信息
    SystemInterruptInformation = 23,     // 中断计数信息
    SystemExceptionInformation = 33,     // 异常计数信息
    SystemRegistryQuotaInformation = 37, // 注册表配额使用情况
    SystemLookasideInformation = 45      // 内核 Lookaside 列表使用情况
    // 更多枚举项可以参考 ReactOS 或 Process Hacker 源码
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryOffset;                // 下一个结构的偏移（用于遍历）
    ULONG NumberOfThreads;                // 线程数
    LARGE_INTEGER WorkingSetPrivateSize;  // 工作集私有大小（Vista+）
    ULONG HardFaultCount;                 // 硬错误计数（Vista+）
    ULONG NumberOfThreadsHighWatermark;   // 线程数峰值
    ULONGLONG CycleTime;                  // CPU 周期计数（Vista+）
    LARGE_INTEGER CreateTime;             // 进程创建时间
    LARGE_INTEGER UserTime;               // 用户态运行时间
    LARGE_INTEGER KernelTime;             // 内核态运行时间
    UNICODE_STRING ImageName;             // 显示名称（进程名）
    KPRIORITY BasePriority;               // 进程基优先级
    HANDLE UniqueProcessId;               // 进程 PID
    HANDLE InheritedFromUniqueProcessId;  // 父进程 PID
    ULONG HandleCount;                    // 句柄数
    ULONG SessionId;                      // 会话 ID
    SIZE_T PeakVirtualSize;               // 峰值虚拟内存大小
    SIZE_T VirtualSize;                   // 当前虚拟内存大小
    ULONG PageFaultCount;                // 页错误计数
    SIZE_T PeakWorkingSetSize;           // 峰值工作集
    SIZE_T WorkingSetSize;               // 当前工作集
    SIZE_T QuotaPeakPagedPoolUsage;      // 分页池配额峰值
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;                // 页面文件使用
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;    // I/O 读次数
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;     // I/O 读字节数
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
    // 后面是线程信息 SYSTEM_THREAD_INFORMATION[]，长度 NumberOfThreads
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

*/

// 手动定义函数指针类型
typedef NTSTATUS(NTAPI* PNtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
    );
int main() {
    // 加载 ntdll.dll
    HMODULE hNtdll = LoadLibraryW(L"ntdll.dll");
    if (!hNtdll) {
        std::wcerr << L"加载 ntdll.dll 失败，错误码: " << GetLastError() << std::endl;
        return 1;
    }

    // 获取 NtQuerySystemInformation 函数地址
    PNtQuerySystemInformation NtQuerySystemInformation =
        (PNtQuerySystemInformation)GetProcAddress(hNtdll, "NtQuerySystemInformation");

    if (!NtQuerySystemInformation) {
        std::wcerr << L"无法找到 NtQuerySystemInformation，错误码: " << GetLastError() << std::endl;
        return 1;
    }

    // 尝试分配缓冲区并查询信息
    ULONG length = 0;
    NTSTATUS status = NtQuerySystemInformation(SystemProcessInformation, nullptr, 0, &length);//第一次调用返回需要的缓冲区大小
    std::vector<BYTE> buffer(length);  //从第一次调用获取缓冲区大小后， 分配缓冲区
    status = NtQuerySystemInformation(SystemProcessInformation, buffer.data(), length, &length);

    if (status != 0) {
        std::wcerr << L"NtQuerySystemInformation 调用失败，状态码: " << std::hex << status << std::endl;
        return 1;
    }

    // 遍历进程列表
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    SYSTEM_PROCESS_INFORMATION* info = reinterpret_cast<SYSTEM_PROCESS_INFORMATION*>(buffer.data());//转换成结构体指针
    while (true) {   
        std::wcout << L"进程名: ";
        if (info->ImageName.Buffer) {
            std::wcout << std::wstring(info->ImageName.Buffer, info->ImageName.Length / sizeof(WCHAR));
            //ImageName.Buffer不一定是空字符结尾
        }
        else {
            std::wcout << L"(没有获取到进程名)";
        }
        std::wcout << L" | PID: " << reinterpret_cast<long long>(info->UniqueProcessId) << std::endl;
        //无符号整数 DWORD_PTR，__int64/__int32, 跟LONG LONG类似

        if (info->NextEntryOffset == 0) break;
        info = reinterpret_cast<SYSTEM_PROCESS_INFORMATION*>( reinterpret_cast<BYTE*>(info)  + info->NextEntryOffset);
    }

    return 0;

}