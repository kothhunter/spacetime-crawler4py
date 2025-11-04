#ifndef QUEUESTACK_TPP
#define QUEUESTACK_TPP

#include <sstream> // Include this to use std::ostringstream
#include <stdexcept>

template <typename T>
void QueueStack<T>::push(const T& value) {
    q.enqueue(item);

    for (size_t i = 0; i < q.size() - 1; ++i) {
        T temp = q.dequeue();
        q.enqueue(temp);
    }
}

template <typename T>
T QueueStack<T>::pop() {
    if (q.isEmpty()) throw std::runtime_error("Cannot pop from an empty stack.");
    return q.dequeue();
}

template <typename T>
T QueueStack<T>::peek() const {
    if (q.isEmpty()) throw std::runtime_error("Cannot peek at an empty stack.");
    return q.peek();
}

template <typename T>
bool QueueStack<T>::isEmpty() const {
    return q.isEmpty();
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