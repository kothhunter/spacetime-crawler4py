#ifndef CIRCULARARRAY_HPP
#define CIRCULARARRAY_HPP

#include "ArrayList.hpp"

template <typename T>
class CircularArray : public ArrayList<T> {
private:
    size_t front; // Index of the front element
    size_t rear;  // Index of the rear element
    bool full;    // Flag to track if the circular array is full

public:
    // Constructor
    CircularArray(size_t initialCapacity = 2, size_t resizeFactor = 2);

    // Add an element to the rear of the circular array
    void enqueue(const T& item);

    // Remove and return the element from the front of the circular array
    T dequeue();

    // Get the element at the front without removing it
    T peek() const;

    // Check if the circular array is empty
    bool isEmpty() const;

    // Check if the circular array is full
    bool isFull() const;

private:
    // Helper method to resize and rearrange elements
    void resize();
};

#include "CircularArray.tpp"

#endif // CIRCULARARRAY_HPP