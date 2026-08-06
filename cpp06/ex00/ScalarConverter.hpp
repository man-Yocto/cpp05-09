#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <cctype>
#include <limits>

class ScalarConverter
{
    public:
        enum Type
        {
            TYPE_CHAR,
            TYPE_INT,
            TYPE_FLOAT,
            TYPE_DOUBLE,
            TYPE_SPECIAL,
            TYPE_INVALID
        };

        static Type detectType(const std::string& literal);
        static void convert(const std::string& literal);

    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();
};

#endif