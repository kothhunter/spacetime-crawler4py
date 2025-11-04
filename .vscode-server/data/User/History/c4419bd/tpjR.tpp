#include "CircularArray.hpp"
#include <stdexcept>

template <typename T>
CircularArray<T>::CircularArray(size_t initialCapacity, size_t resizeFactor)
    : ArrayList<T>(initialCapacity, resizeFactor), front(0), rear(0), full(false) {}

template <typename T>
void CircularArray<T>::enqueue(const T& item) {
    if (isFull()) {
        resize();
    }

    this->data[rear] = item;
    rear = (rear + 1) % this->capacity;

    if (rear == front) {
        full = true;
    }
}

template <typename T>
T CircularArray<T>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Cannot dequeue from an empty CircularArray");
    }

    T item = this->data[front];
    front = (front + 1) % this->capacity;
    full = false;

    return item;
}

template <typename T>
T CircularArray<T>::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Cannot peek from an empty CircularArray");
    }
    return this->data[front];
}

template <typename T>
bool CircularArray<T>::isEmpty() const {
    return (!full && (front == rear));
}

template <typename T>
bool CircularArray<T>::isFull() const {
    return full;
}

template <typename T>
void CircularArray<T>::resize() {
    size_t newCapacity = this->capacity * this->resizeFactor;
    T* newData = new T[newCapacity];

    size_t currentSize = this->capacity;
    
    for (size_t i = 0; i < currentSize; ++i) {
        newData[i] = this->data[(front + i) % this->capacity];
    }

    delete[] this->data;
    this->data = newData;
    this->capacity = newCapacity;
    front = 0;
    rear = currentSize;
    full = false;
}
