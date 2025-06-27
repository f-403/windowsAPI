// 2.2卷管理.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <vector>
int main()
{
    /*
    BOOL GetVolumeInformationA(
  [in, optional]  LPCSTR  lpRootPathName,
  [out, optional] LPSTR   lpVolumeNameBuffer,
  [in]            DWORD   nVolumeNameSize,
  [out, optional] LPDWORD lpVolumeSerialNumber,
  [out, optional] LPDWORD lpMaximumComponentLength,
  [out, optional] LPDWORD lpFileSystemFlags,
  [out, optional] LPSTR   lpFileSystemNameBuffer,
  [in]            DWORD   nFileSystemNameSize
);
    */
    
    wchar_t volum_data[MAX_PATH+1]{};//卷名 , 就是你电脑的硬盘起的名字
    DWORD lengthname = MAX_PATH;
    wchar_t filesystemname[MAX_PATH+1];//卷系统名， 如NTFS/FAT32
    BOOL check = GetVolumeInformation(
        LR"(\\?\Volume{4b138497-138d-11ee-9300-a9b2b55c06e0}\)", /*/注意， 只能写根目录， 不能这样写 C:\TEST\1223\。只能写C:\, D:\ 或GUID*/
        volum_data,
        MAX_PATH,
        NULL,
        &lengthname,
        NULL,
        filesystemname,
        MAX_PATH);
    if (!check) {
        std::cout << "没有查询到信息" << std::endl;
        std::cout << GetLastError() << std::endl;
        return 0;
    }
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    std::wcout << volum_data << std::endl;
    std::wcout << filesystemname << std::endl;


    std::wcout << L"----------查找所有卷-----------" << std::endl;
    //枚举卷
    wchar_t test[MAX_PATH + 1];
    HANDLE fh = FindFirstVolume(test,MAX_PATH);
    if (fh == INVALID_HANDLE_VALUE) {
        std::wcout << "第一次查找卷出错" << std::endl;
        std::wcout << GetLastError() << std::endl;
        return 0;
    }
    //
    // 处理第一个卷
    std::wcout << L"找到卷: " << test << std::endl;

    DWORD size_of_name = 0;
    if (!GetVolumePathNamesForVolumeNameW(test, NULL, 0, &size_of_name) &&
        GetLastError() != ERROR_MORE_DATA) {
        std::wcerr << L"获取缓冲区大小失败，错误码: " << GetLastError() << std::endl;
    }
    else {
        std::vector<wchar_t> vname(size_of_name);
        if (GetVolumePathNamesForVolumeNameW(test, vname.data(), size_of_name, &size_of_name)) {
            if (*vname.data() == L'\0') {
                std::wcout << L"(该卷没有挂载路径)" << std::endl;
            }
            else {
                for (wchar_t* p = vname.data(); *p != L'\0'; p += wcslen(p) + 1) {
                    std::wcout << L"卷挂载路径: " << p << std::endl;
                }
            }
        }
    }

    // 接着处理后续卷
    for (;;) {
        
        BOOL check = FindNextVolume(fh, test, MAX_PATH);
        if (GetLastError() == ERROR_NO_MORE_FILES) {
            std::wcout << L"没有更多卷" << std::endl;
            break;
        }
        if (!check) {
            std::wcout << L"查找所有卷出错" << std::endl;
            break;
        }  
        std::wcout << L"找到卷:" << test << std::endl;

     
        
        std::wcout << test << std::endl;
        DWORD size_of_name = 0;
        if (!GetVolumePathNamesForVolumeNameW(test, NULL, 0, &size_of_name) &&
            GetLastError() != ERROR_MORE_DATA) {
            std::wcerr << L"获取缓冲区大小失败，错误码: " << GetLastError() << std::endl;
            return 1;
        }

        std::vector<wchar_t> vname(size_of_name);

        if (!GetVolumePathNamesForVolumeNameW(test, vname.data(), size_of_name, &size_of_name)) {
            std::wcerr << L"获取卷路径名失败，错误码: " << GetLastError() << std::endl;
            return 1;
        }
        //--------------------------------------------------
        if (*vname.data() == L'\0') {
            std::wcout << L"(该卷没有挂载路径)" << std::endl;
            continue;
        }
        // 输出所有路径
        for (wchar_t* p = vname.data(); *p != L'\0'; p += wcslen(p) + 1) {
            std::wcout << L"卷挂载路径: " << p << std::endl;
        }
    
    }
    FindVolumeClose(fh);


    //如果要进一步查询卷名对应的盘符， 如c: d:, 要做如下操作
    //1.获取卷的挂载点（盘符）
    //  使用 GetVolumePathNamesForVolumeNameW 获取卷对应的盘符（如 C : \）。
    //2.查询卷信息
    //  使用 GetVolumeInformationW 获取卷的详细信息（名称、文件系统、序列号等）。


}

