#include <iostream>
#include <string>
using namespace std;

constexpr int STK_MAX = 1000; // Define the stack capacity

class Stack {
private:
    int _top;               // Index of the top element
    char buf[STK_MAX];      // Array to hold stack elements

public:
    // Constructor: Initializes the stack
    Stack() : _top(-1) {}

    // Adds a character to the stack
    void push(char c) {
        if (isFull()) {
            cerr << "Error: Stack overflow. Cannot push '" << c << "' onto the stack.\n";
            return;
        }
        buf[++_top] = c;
    }

    // Removes and returns the top character
    char pop() {
        if (isEmpty()) {
            cerr << "Error: Stack underflow. Returning '@'.\n";
            return '@';
        }
        return buf[_top--];
    }

    // Returns the top character without removing it
    char top() const {
        if (isEmpty()) {
            cerr << "Error: Stack is empty. Returning '@'.\n";
            return '@';
        }
        return buf[_top];
    }

    // Checks if the stack is empty
    bool isEmpty() const {
        return _top == -1;
    }

    // Checks if the stack is full
    bool isFull() const {
        return _top == STK_MAX - 1;
    }
};

// Pushes all characters from a string onto the stack
void push_all(Stack& stk, const string& line) {
    for (char c : line) {
        stk.push(c);
    }
}

// Pops all characters from the stack and prints them
void pop_all(Stack& stk) {
    while (!stk.isEmpty()) {
        cout << stk.pop();
    }
    cout << endl;
}
