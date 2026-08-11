#include "RPN.hpp"

#include <cctype>
#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN& other) : _stack(other._stack)
{
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN()
{
}

bool RPN::isNumber(const std::string& token) const
{
    return token.length() == 1
        && std::isdigit(static_cast<unsigned char>(token[0]));
}

bool RPN::isOperator(const std::string& token) const
{
    return token.length() == 1
        && (token[0] == '+' || token[0] == '-' || token[0] == '*'
            || token[0] == '/');
}

void RPN::applyOperator(const std::string& op)
{
    int a;
    int b;
    int result;

    if (_stack.size() < 2)
        throw std::runtime_error("Error");
    b = _stack.top();
    _stack.pop();
    a = _stack.top();
    _stack.pop();
    if (op == "+")
        result = a + b;
    else if (op == "-")
        result = a - b;
    else if (op == "*")
        result = a * b;
    else
    {
        if (b == 0)
            throw std::runtime_error("Error");
        result = a / b;
    }
    _stack.push(result);
}

int RPN::evaluate(const std::string& expression)
{
    //this will open the string stream to read from the string
    std::stringstream stream(expression);
    std::string token;

    while (!_stack.empty())
        _stack.pop();
    //this will read from a string exactly one character at a time and store it in the token variable ignoring whitespace
    while (stream >> token)
    {
        if (isNumber(token))
            _stack.push(token[0] - '0');
        else if (isOperator(token))
            applyOperator(token);
        else
            throw std::runtime_error("Error");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");
    return _stack.top();
}
