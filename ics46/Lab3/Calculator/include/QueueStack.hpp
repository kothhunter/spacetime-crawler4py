#ifndef QUEUESTACK_HPP
#define QUEUESTACK_HPP

#include "CircularArray.hpp"
#include <stdexcept>

template <typename T>
class QueueStack {
public:
    QueueStack() = default;
    void push(const T& value); // Push an element onto the stack
    T pop();                // Remove the top element from the stack
    T peek() const;             // Get the top element of the stack
    bool isEmpty() const;      // Check if the stack is empty
    std::string toString() const; // String representation of the stack

private:
    CircularArray<T> q1; // Primary queue
    CircularArray<T> q2; // Secondary queue used for operations
};

#include "QueueStack.tpp" // Include template implementation
#endif // QUEUESTACK_HPP