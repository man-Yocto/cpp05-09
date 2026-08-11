#include "BitcoinExchange.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange exchange;
        try
        {
            exchange.loadDatabase("data.csv");
        }
        catch (const std::exception&)
        {
            exchange.loadDatabase("../cpp_09/cpp_09/data.csv");
        }
        exchange.processInputFile(argv[1]);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
