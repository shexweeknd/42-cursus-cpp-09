#include "RPN.hpp"

void RPN(std::string input)
{
    std::istringstream iss(input);
    std::string token;
    
    int first;
    int second;

    if ((!(iss >> first) || !(iss >> second)) || (first > 10 || second > 10))
    {
        std::cout << "\e[31mError\e[0m" << std::endl;
        return ;
    }

    std::stack<int> _stack;
    _stack.push(first); _stack.push(second);

    while (iss >> token)
    {
        if (atoi(token.c_str()) >= 10)
        {
            std::cout << "\e[31mError\e[0m" << std::endl;
            return ;
        }
        if (!token.compare("+") 
            || !token.compare("-")
            || !token.compare("*")
            || !token.compare("/"))
        {
            first = _stack.top(); _stack.pop();
            second = _stack.top(); _stack.pop();

            if (!token.compare("+")) _stack.push(second + first); 
            if (!token.compare("-")) _stack.push(second - first); 
            if (!token.compare("*")) _stack.push(second * first); 
            if (!token.compare("/")) _stack.push(second / first); 
        }
        else
            _stack.push(atoi(token.c_str()));
    }

    if (_stack.size() == 1)
        std::cout << _stack.top() << std::endl;
    else
        std::cout << "\e[31mError\e[0m" << std::endl;
}
