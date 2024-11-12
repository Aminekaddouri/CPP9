#include "RPN.hpp"

RPN::RPN() {};

RPN::RPN(const RPN &other)
{
    stack = other.stack; // Shallow copy is sufficient since std::stack manages its own memory
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        stack = other.stack;
    return (*this);
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string &token) const
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::preformOperation(const std::string &op, int a, int b)
{
    if (op == "+")
        return (a + b);
    if (op == "-")
        return (a - b);
    if (op == "*")
        return (a * b);
    if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Error: Division by zero");
        return (a / b);
    }
    throw std::runtime_error("Error: invalid operator");
}

void RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    try
    {
        while (iss >> token)
        {
            if (isOperator(token))
            {
                if (stack.size() < 2)
                    throw std::runtime_error("Error: Insufficient operands");
                int b = stack.top();
                stack.pop();
                int a = stack.top();
                stack.pop();
                stack.push(preformOperation(token, a, b));
            }
            else
            {
                std::istringstream tokenStream(token);
                int number;
                if (!(tokenStream >> number)) {
                    throw std::runtime_error("Error");
                }
                stack.push(number);
            }
        }
        if (stack.size() != 1)
            throw std::runtime_error("Error: Invalid expression");
        std::cout << stack.top() << std::endl; // Output the result
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
}