#include <iostream>
using namespace std;
#include "stack.hpp"

int main()
{
    Stack stack;
    string line;
    while (getline(cin, line))
    {
        push_all(stack, line);
        pop_all(stack);
    }
    return 0;
}
