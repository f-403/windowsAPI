#include <windows.h>
#include <tchar.h>
#include <iostream>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    DWORD pid;
    if (GetWindowThreadProcessId(hwnd, &pid)) {//如果出错， 返回0,获取窗口进程ID

        TCHAR title[256];
        if (GetWindowText(hwnd, title, 256)) {
            _tprintf(TEXT("窗口句柄: %p\t进程ID: %u\t标题: %s\n"), hwnd, pid, title);
        }
    }
    return TRUE;
}

int main() {
    EnumWindows(EnumWindowsProc, 0);
    return 0;
}