#include "whatever.hpp"
#include <iostream>
#include <string>

int main(void)
{
    int a = 2;
    int b = 3;
    ::swap(a, b);
    std::cout << "int swap: a = " << a << ", b = " << b << std::endl;
    std::cout << "min(2, 3) = " << ::min(2, 3) << std::endl;
    std::cout << "max(2, 3) = " << ::max(2, 3) << std::endl;

    int x = 5;
    int y = 5;
    std::cout << "min(5, 5) = " << ::min(x, y) << std::endl;
    std::cout << "max(5, 5) = " << ::max(x, y) << std::endl;

    std::string s1 = "hello";
    std::string s2 = "world";
    ::swap(s1, s2);
    std::cout << "string swap: s1 = " << s1 << ", s2 = " << s2 << std::endl;

    return 0;
}
