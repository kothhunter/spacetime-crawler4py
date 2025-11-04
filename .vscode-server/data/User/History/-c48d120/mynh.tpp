#ifndef QUEUESTACK_TPP
#define QUEUESTACK_TPP

#include <sstream> // Include this to use std::ostringstream
#include <stdexcept>

template <typename T>
void QueueStack<T>::push(const T& value) {
    q1.enqueue(item);

    int size = q1.size();
    for (int i = 0; i < size - 1; ++i) {
        T temp = q1.dequeue();
        q1.enqueue(temp);
    }
}

template <typename T>
T QueueStack<T>::pop() {
    if (q1.isEmpty()) {
        throw std::underflow_error("Cannot pop from an empty stack");
    }
    return q1.dequeue();
}

template <typename T>
T QueueStack<T>::peek() const {
    if (q1.isEmpty()) {
        throw std::underflow_error("Cannot peek from an empty stack");
    }
    return q1.peek();
}

template <typename T>
bool QueueStack<T>::isEmpty() const {
    return q1.isEmpty();
}

template <typename T>
std::string QueueStack<T>::toString() const {
    std::ostringstream out;
    CircularArray<T> tempQueue = q1; // Make a copy of q1 to preserve its state

    while (!tempQueue.isEmpty()) {
        out << tempQueue.dequeue() << '\n'; // Dequeue elements from the copy
    }

    out << "---\n"; // Separator to indicate the bottom of the stack
    return out.str();

}

#endif // QUEUESTACK_TPP