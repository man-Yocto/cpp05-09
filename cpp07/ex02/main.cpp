#include "Array.hpp"
#include <iostream>
#include <string>
#include <exception>

int main(void)
{
    Array<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Array<int> b(a);
    b[0] = 99;
    std::cout << "a[0] = " << a[0] << ", b[0] = " << b[0] << std::endl;

    Array<int> c;
    c = a;
    c[1] = 42;
    std::cout << "a[1] = " << a[1] << ", c[1] = " << c[1] << std::endl;

    Array<int> empty;
    std::cout << "empty size = " << empty.size() << std::endl;

    try
    {
        std::cout << a[5] << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "out of bounds" << std::endl;
    }

    Array<std::string> words(2);
    words[0] = "hello";
    words[1] = "world";
    std::cout << "words[0] = " << words[0] << std::endl;

    return 0;
}
