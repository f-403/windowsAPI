// 1.5文件加解密.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
int main()
{
    /*
    加密字节 = (原字节 + shift) % 256  # 无需提前 shift%256
    解密字节 = (加密字节 - shift) % 256
    */
    std::string name = "abcd";
    std::vector<unsigned char>sec;//存放加密字符串
    
    int key = 2;
    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i] << std::endl;
        std::cout << int(name[i]) << std::endl;
        unsigned char swap = (unsigned char)((int(name[i]) + key) % 256);
        sec.push_back(swap);
        std::cout << swap << std::endl;
    }
    sec.push_back('\0');
    std::cout << "加密前字符串为:" << name << std::endl;
    std::cout << "加密后字符串为:" << sec.data() << std::endl;

    //解密过程
    std::vector<unsigned char>not_sec;//存放加密字符串
    std::cout << (unsigned char)  ((int(sec[0])-key)%256) << std::endl;
}

