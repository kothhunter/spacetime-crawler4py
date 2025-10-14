#include <iostream>
#include <string>
using namespace std;

constexpr int STK_MAX = 1000; 

class Stack {
private:
    int _top;              
    char buf[STK_MAX];      

public:
    Stack() : _top(-1) {}

    void push(char c) {
        if (isFull()) {
            cerr << "Error: Stack overflow. Cannot push '" << c << "' onto the stack.\n";
            return;
        }
        buf[++_top] = c;
    }

    char pop() {
        if (isEmpty()) {
            cerr << "Error: Stack underflow. Returning '@'.\n";
            return '@';
        }
        return buf[_top--];
    }

    char top() const {
        if (isEmpty()) {
            cerr << "Error: Stack is empty. Returning '@'.\n";
            return '@';
        }
        return buf[_top];
    }

    bool isEmpty() const {
        return _top == -1;
    }

    bool isFull() const {
        return _top == STK_MAX - 1;
    }
};

void push_all(Stack& stack, const string& line) {
    for (char c : line) {
        stack.push(c);
    }
}

void pop_all(Stack& stack) {
    while (!stack.isEmpty()) {
        cout << stack.pop();
    }
    cout << endl;
}
