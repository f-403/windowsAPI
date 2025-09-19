// 2.信息处理程序wndproc-固定返回值与固定参数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

LRESULT CALLBACK my_WndProc(
    HWND   hWnd,     // 窗口句柄（哪个窗口收到的消息？）
    UINT   msg,      // 消息标识（如 WM_KEYDOWN、WM_PAINT）
    WPARAM wParam,   // 附加信息（如按键的虚拟键码）
    LPARAM lParam    // 扩展信息（如按键的重复计数、扫描码等）
); //自定义信息处理函数

int main()
{
    //这程序不是GUI， 下面的my_WndProc不能获取键盘输入， 这只是一个写法例子

    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}

LRESULT CALLBACK my_WndProc(
    HWND   hWnd,     // 窗口句柄（哪个窗口收到的消息？）
    UINT   msg,      // 消息标识（如 WM_KEYDOWN、WM_PAINT）
    WPARAM wParam,   // 附加信息（如按键的虚拟键码）
    LPARAM lParam    // 扩展信息（如按键的重复计数、扫描码等）
) {
    switch (msg) {

    case WM_CLOSE:
        PostQuitMessage(0);//退出消息处理程序
    case WM_DESTROY:
        break;
    case WM_KEYDOWN:
        std::cout << "按下了虚拟键:" << wParam << std::endl;
        
    }
    return 0;
    //如果不返回0, 要 return DefWindowProc(hWnd, msg, wParam, lParam)，让另一个程序处理，只管return过去就行
}

/*
msg类型
WM_DESTROY 关闭程序收到的信息
WM_KEYDOWN 按下, 虚 拟字符码， 如vk_a
WM_CHAR 实际字符， 如'a'
WM_CLOSE 用户请求关闭窗口
*/