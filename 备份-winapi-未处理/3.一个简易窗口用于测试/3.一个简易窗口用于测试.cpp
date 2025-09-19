// 3.一个简易窗口用于测试.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main()
{
    // 1. 注册窗口类（最简版）
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"MyWin";
    RegisterClass(&wc);

    // 2. 创建窗口（仅保留必要参数）
    HWND hWnd = CreateWindow(
        L"MyWin", L"简易窗口", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, wc.hInstance, NULL
    );
    ShowWindow(hWnd, SW_SHOW);
    MSG msg;
    while (GetMessage(&msg,hWnd, 0,0) ){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// 简化版窗口过程
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if (wParam == VK_LEFT && (GetKeyState(VK_CONTROL) & 0x8000)) {//跟>> 15后&1一样
                std::cout << "Ctrl+左方向键" << std::endl;
            }
            break;
        case WM_CHAR: {
            //检查ctrl, shift
            BOOL isCtrlPressed = ((GetKeyState(VK_CONTROL) >> 15) & 1);
            BOOL isShiftPressed = ((GetKeyState(VK_SHIFT) >> 15) & 1);
            if (isCtrlPressed) {
                std::wcout << "ctrl + " << (wchar_t)wParam << std::endl;
            }
            if (isShiftPressed) {
                std::wcout << L"shift + " << (wchar_t)wParam << std::endl;
            }
            if ((!isCtrlPressed) && (!isShiftPressed)) {
                std::wcout <<  L"wParam: " << (wchar_t)wParam << std::endl;
            }
            break;
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
