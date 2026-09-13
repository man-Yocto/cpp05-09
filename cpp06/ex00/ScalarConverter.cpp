#include "ScalarConverter.hpp"
#include <iomanip>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

bool is_int(const std::string& literal)
{
    if (literal.empty())
        return false;

    size_t start = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;

    if (start == literal.length())
        return false;

    for (size_t i = start; i < literal.length(); ++i)
        if (!std::isdigit(static_cast<unsigned char>(literal[i])))
            return false;

    return true;
}

bool is_float(const std::string& literal)
{
    if (literal.empty() || literal[literal.length() - 1] != 'f')
        return false;

    size_t start = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;

    if (start >= literal.length() - 1)
        return false;

    bool hasDecimalPoint = false, hasDigit = false;

    for (size_t i = start; i < literal.length() - 1; ++i)
    {
        if (literal[i] == '.')
        {
            if (hasDecimalPoint) return false;
            hasDecimalPoint = true;
        }
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
            hasDigit = true;
        else
            return false;
    }

    return hasDecimalPoint && hasDigit;
}

bool is_double(const std::string& literal)
{
    if (literal.empty())
        return false;

    size_t start = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;

    if (start == literal.length())
        return false;

    bool hasDecimalPoint = false, hasDigit = false;

    for (size_t i = start; i < literal.length(); ++i)
    {
        if (literal[i] == '.')
        {
            if (hasDecimalPoint) return false;
            hasDecimalPoint = true;
        }
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
            hasDigit = true;
        else
            return false;
    }

    return hasDecimalPoint && hasDigit;
}

bool is_char(const std::string& literal)
{
    return literal.length() == 1 &&
           std::isalpha(static_cast<unsigned char>(literal[0]));
}

static bool is_special(const std::string& literal)
{
    return literal == "nan" || literal == "+inf" || literal == "-inf" ||
           literal == "nanf" || literal == "+inff" || literal == "-inff";
}

ScalarConverter::Type ScalarConverter::detectType(const std::string& literal)
{
    if (is_special(literal)) return TYPE_SPECIAL;
    if (is_char(literal)) return TYPE_CHAR;
    if (is_int(literal)) return TYPE_INT;
    if (is_float(literal)) return TYPE_FLOAT;
    if (is_double(literal)) return TYPE_DOUBLE;
    return TYPE_INVALID;
}

static void printCharAndInt(double value)
{
    if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<unsigned char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;

    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;
}

void printFromChar(char c)
{
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

void printFromInt(long value)
{
    if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<unsigned char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;

    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << value << std::endl;

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << std::endl;
}

void printFromFloat(float value)
{
    std::cout << std::fixed << std::setprecision(1);
    printCharAndInt(static_cast<double>(value));
    std::cout << "float: " << value << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << std::endl;
}

void printFromDouble(double value)
{
    std::cout << std::fixed << std::setprecision(1);
    printCharAndInt(value);
    std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    std::cout << "double: " << value << std::endl;
}

void printSpecial(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (literal == "nan" || literal == "nanf")
        std::cout << "float: nanf" << std::endl << "double: nan" << std::endl;
    else if (literal == "+inf" || literal == "+inff")
        std::cout << "float: +inff" << std::endl << "double: +inf" << std::endl;
    else
        std::cout << "float: -inff" << std::endl << "double: -inf" << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    Type type = detectType(literal);
    char* end;
    errno = 0;

    if (type == TYPE_INVALID)
    {
        std::cout << "Error: Invalid input" << std::endl;
        return;
    }

    if (type == TYPE_SPECIAL)
    {
        printSpecial(literal);
        return;
    }

    if (type == TYPE_CHAR)
    {
        printFromChar(literal[0]);
        return;
    }

    if (type == TYPE_INT)
    {
        long value = std::strtol(literal.c_str(), &end, 10);

        if (*end != '\0')
        {
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            return;
        }

        if (errno == ERANGE ||
            value < std::numeric_limits<int>::min() ||
            value > std::numeric_limits<int>::max())
        {
            double asDouble = std::strtod(literal.c_str(), &end);
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "float: " << static_cast<float>(asDouble) << "f" << std::endl;
            std::cout << "double: " << asDouble << std::endl;
        }
        else
            printFromInt(value);

        return;
    }

    if (type == TYPE_FLOAT)
    {
        double value = std::strtod(literal.c_str(), &end);

        if (errno == ERANGE || *end != 'f' || end[1] != '\0')
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
        else
            printFromFloat(static_cast<float>(value));

        return;
    }

    if (type == TYPE_DOUBLE)
    {
        double value = std::strtod(literal.c_str(), &end);

        if (errno == ERANGE || *end != '\0')
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
        else
            printFromDouble(value);

        return;
    }
}