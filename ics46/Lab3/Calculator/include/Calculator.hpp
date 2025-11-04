#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include "QueueStack.hpp" 

class Calculator {
public:
    Calculator();
    void run();

private:
    QueueStack<int> memory; // Stack to hold numbers in memory

    void processOperation(const std::string& line);
    int performOperation(char op, int first, int second);
};

#endif // CALCULATOR_HPP