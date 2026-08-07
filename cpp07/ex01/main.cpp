#include "iter.hpp"
#include <iostream>
#include <string>

void printInt(int value)
{
    std::cout << value << " ";
}

void printString(const std::string& value)
{
    std::cout << value << " ";
}

void increment(int& value)
{
    ++value;
}

int main(void)
{
    int numbers[4] = {1, 2, 3, 4};
    std::cout << "ints: ";
    iter(numbers, 4, printInt);
    std::cout << std::endl;

    int modified[4] = {1, 2, 3, 4};
    iter(modified, 4, increment);
    std::cout << "incremented: ";
    iter(modified, 4, printInt);
    std::cout << std::endl;

    std::string words[3] = {"hello", "world", "!"};
    std::cout << "strings: ";
    iter(words, 3, printString);
    std::cout << std::endl;

    return 0;
}
