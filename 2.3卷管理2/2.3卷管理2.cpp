// 2.3卷管理2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    //utf-8
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    wchar_t volumeName[MAX_PATH + 1];
    HANDLE hVol = FindFirstVolumeW(volumeName, ARRAYSIZE(volumeName));
    if (hVol == INVALID_HANDLE_VALUE) {
        std::wcerr << L"查找卷失败: " << GetLastError() << std::endl;
        return 1;
    }

    do {
        std::wcout << L"卷 GUID: " << volumeName << std::endl;

        wchar_t label[MAX_PATH] = {};
        wchar_t fsName[MAX_PATH] = {};
        DWORD serial = 0, maxCompLen = 0, fsFlags = 0;

        // 这里直接使用卷 GUID 调用
        if (GetVolumeInformationW(
            volumeName,
            label,
            ARRAYSIZE(label),
            &serial,
            &maxCompLen,
            &fsFlags,
            fsName,
            ARRAYSIZE(fsName))) {

            std::wcout << L"  卷标签: " << label << std::endl;
            std::wcout << L"  文件系统: " << fsName << std::endl;
            std::wcout << L"  卷序列号: " << std::hex << serial << std::endl;
        }
        else {
            std::wcerr << L"  获取卷信息失败: " << GetLastError() << std::endl;
        }

    } while (FindNextVolumeW(hVol, volumeName, ARRAYSIZE(volumeName)));

    FindVolumeClose(hVol);

}
