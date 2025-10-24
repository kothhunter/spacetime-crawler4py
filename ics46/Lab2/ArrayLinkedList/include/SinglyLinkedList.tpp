#include "SinglyLinkedList.hpp"

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), n(0) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    while (!isEmpty()) {
        remove();
    }
}

// Copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), n(0) {
    Node* current = other.head;
    while (current != nullptr) {
        add(current->item); // Add each item to the new list
        current = current->next;
    }
}

// Copy assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    if (this != &other) { // Avoid self-assignment
        clear(); // Clear the current list

        Node* current = other.head;
        while (current != nullptr) {
            add(current->item); // Add each item to the new list
            current = current->next;
        }
    }
    return *this;
}

// Helper function to clear the list
template <typename T>
void SinglyLinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(); // Remove all elements
    }
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return n == 0;
}

template <typename T>
size_t SinglyLinkedList<T>::size() const {
    return n;
}

template <typename T>
void SinglyLinkedList<T>::rangeCheck(size_t index) const {
    if (index >= n) {
        throw std::out_of_range("Index out of bounds");
    }
}

template <typename T>
T SinglyLinkedList<T>::get(size_t index) const {
    rangeCheck(index);
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->item;
}

template <typename T>
void SinglyLinkedList<T>::add(const T& item) {
    Node* newNode = new Node(item, head);
    head = newNode;
    if (tail == nullptr) { // If the list was empty, update the tail
        tail = head;
    }
    ++n;
}

template <typename T>
void SinglyLinkedList<T>::add(size_t index, const T& item) {
    if (index > n) {
        throw std::out_of_range("Index out of bounds");
    }

    if (index == 0) {
        add(item);
        return;
    }

    if (index == n) {
        addLast(item);
        return;
    }

    Node* prev = head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }

    Node* newNode = new Node(item, prev->next);
    prev->next = newNode;
    ++n;
}

template <typename T>
T SinglyLinkedList<T>::remove() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node* oldHead = head;
    T item = oldHead->item;
    head = head->next;
    if (head == nullptr) { // If the list becomes empty, update the tail
        tail = nullptr;
    }
    delete oldHead;
    --n;
    return item;
}

template <typename T>
T SinglyLinkedList<T>::remove(size_t index) {
    rangeCheck(index);

    if (index == 0) {
        return remove();
    }

    Node* prev = head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }

    Node* target = prev->next;
    T item = target->item;

    prev->next = target->next;
    if (target == tail) {
        tail = prev;
    }

    delete target;
    --n;
    return item;
}


template <typename T>
void SinglyLinkedList<T>::addLast(const T& item) {
    Node* newNode = new Node(item);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++n;
}

template <typename T>
T SinglyLinkedList<T>::removeLast() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    // note: in the case there is only one node
    if (head == tail) {
        T item = head->item;
        delete head;
        head = tail = nullptr;
        n = 0;
        return item;
    }

    Node* prev = head;
    while (prev->next != tail) {
        prev = prev->next;
    }

    T item = tail->item;
    delete tail;
    tail = prev;
    tail->next = nullptr;
    --n;
    return item;
}