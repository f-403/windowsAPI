#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <locale>

int main() {
   
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8
    std::locale::global(std::locale("")); // 设置全局 locale 为本地系统（通常支持中文）

    // 打开文件（路径支持中文）
    HANDLE hFile = CreateFileW(
        L"test.txt",             // 文件名
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "打开文件失败，错误码: " << GetLastError() << std::endl;
        return 1;
    }

    // 获取文件大小
    LARGE_INTEGER file_size;
    if (!GetFileSizeEx(hFile, &file_size)) {
        std::cerr << "获取文件大小失败" << std::endl;
        CloseHandle(hFile);
        return 1;
    }
    //为了方便，这里没有做过多检测函数返回值是否成功
    //读取文件
    std::vector<char> buff(file_size.QuadPart);//用于存放文件内容
    ReadFile(hFile, buff.data(), file_size.QuadPart, 0, NULL);
    
    //第一次获取缓冲区大小, 利用上面保存的文件内容来获取缓冲区大小
    int check = MultiByteToWideChar(CP_UTF8, 0, buff.data(), -1, NULL, 0);//
    
    //利用缓冲区大小转换成utf8
    std::vector<wchar_t> data(check);
    MultiByteToWideChar(CP_UTF8, 0, buff.data(), -1, data.data(), check);
    std::wcout << L"文件内容是:" << data.data() << std::endl;

   
    return 0;
}
