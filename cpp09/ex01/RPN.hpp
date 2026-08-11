#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    int evaluate(const std::string& expression);

private:
    std::stack<int> _stack;

    bool isOperator(const std::string& token) const;
    bool isNumber(const std::string& token) const;
    void applyOperator(const std::string& op);
};

#endif
