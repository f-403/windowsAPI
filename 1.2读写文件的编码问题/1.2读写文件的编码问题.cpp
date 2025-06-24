// 1.2读写文件的编码问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <vector>
int main()
{
    std::string name = "高州";
    HANDLE f_c = CreateFile(L"1.TXT", GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD count;
    //WriteFile(f_c, name.c_str(), name.size(), &count, NULL);
    //std::cout << "写入了" << count << "个字节" << std::endl;

    DWORD size = GetFileSize(f_c, NULL);
    std::cout << "文件大小为:" << size << "个字节" << std::endl;
    std::vector<char> buff(size + 1);
    buff[size] = '\0';
    
    //文件指针放到前面
    SetFilePointer(f_c, 0, 0, 0);
    if (!ReadFile(f_c,buff.data(),size, &count, NULL)) {
        std::cout << "文件读取失败" << std::endl;
        std::cout << GetLastError() << std::endl;
        return 0;
    }
    std::cout << "读取了" << count << "个字节" << std::endl;
    

    //先转换， 获取字符个数
    int count_ = MultiByteToWideChar(CP_UTF8, 0, buff.data(), size, NULL, 0);
    std::cout << "转换后的字符个数是:" << count_ << std::endl;
    std::vector<wchar_t> swap_data(count_+1);
  
    MultiByteToWideChar(CP_UTF8,0,buff.data(),size,swap_data.data(),count_);
    
    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale("")); //如果下面是用writeconsole打印的话，这两句可以不要


    std::wcout << L"转换后输出:" << swap_data.data() << std::endl;
    //WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),swap_data.data(),swap_data.size(),NULL,NULL);
}

