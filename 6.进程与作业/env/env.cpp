#include <iostream>
#include <Windows.h>
#include <sstream>

int main()
{
    //int a = 123;
    std::stringstream os;
    os << "test";
    std::cout << "写指针变到后面了:" << os.str() << std::endl;
    std::string check{};
    os.seekg(1);
    os >> check;
    std::cout << "读取指针可能在前面:" << check << std::endl;
    
    return 0;
}
