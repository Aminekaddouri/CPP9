#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <sstream>
#include <iostream>

class RPN
{
private:
    std::stack<int> stack;
    bool isOperator(const std::string &token) const;
    int  preformOperation(const std::string &op, int a, int b);

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    void evaluate(const std::string &expression);
};

#endif