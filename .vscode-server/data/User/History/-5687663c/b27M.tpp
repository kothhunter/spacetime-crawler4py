#include "BalancedList.hpp"

// Constructor
template <typename T>
BalancedList<T>::BalancedList(size_t initialArraySize)
    : head(nullptr), tail(nullptr), initialArraySize(initialArraySize), totalSize(0) {}

// Destructor
template <typename T>
BalancedList<T>::~BalancedList() {
    clear();
}

// Copy constructor
template <typename T>
BalancedList<T>::BalancedList(const BalancedList<T>& other)
    : head(nullptr), tail(nullptr), initialArraySize(other.initialArraySize), totalSize(0) {
    Node* current = other.head;
    while (current != nullptr) {
        // Create a new node with a deep copy of the ArrayList
        Node* newNode = new Node(current->array.getCapacity());
        newNode->array = current->array; // Use ArrayList's copy assignment operator
        if (tail == nullptr) {
            head = tail = newNode; // First node in the list
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        current = current->next;
    }
    totalSize = other.totalSize;
}

// Copy assignment operator
template <typename T>
BalancedList<T>& BalancedList<T>::operator=(const BalancedList<T>& other) {
    if (this != &other) { // Avoid self-assignment
        clear(); // Clear the current list

        initialArraySize = other.initialArraySize;
        totalSize = 0;

        Node* current = other.head;
        while (current != nullptr) {
            // Create a new node with a deep copy of the ArrayList
            Node* newNode = new Node(current->array.getCapacity());
            newNode->array = current->array; // Use ArrayList's copy assignment operator
            if (tail == nullptr) {
                head = tail = newNode; // First node in the list
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            current = current->next;
        }
        totalSize = other.totalSize;
    }
    return *this;
}

// Helper function to clear the list
template <typename T>
void BalancedList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp; // Free the memory for the node
    }
    head = tail = nullptr;
    totalSize = 0;
}

// Check if the list is empty
template <typename T>
bool BalancedList<T>::isEmpty() const {
    return totalSize == 0;
}

// Get the total size of the list
template <typename T>
size_t BalancedList<T>::size() const {
    return totalSize;
}

// Check if an index is within range
template <typename T>
void BalancedList<T>::rangeCheck(size_t index) const {
    if (index >= totalSize) {
        throw std::out_of_range("Index out of bounds");
    }
}

// Get an element at a specific index
template <typename T>
T BalancedList<T>::get(size_t index) const {
    rangeCheck(index);
    Node* current = head;
    while (current != nullptr) {
        size_t count = current->array.size();
        if (index < count) {
            return current->array.get(index);
        }
        index -= count;
        current = current->next;
    }
    throw std::out_of_range("Index out of bounds (internal error)");
}

// Add an item to the front of the list
template <typename T>
void BalancedList<T>::add(const T& item) {
    if (head == nullptr) {
        head = new Node(0, nullptr);
        tail = head;
    }

    tail->array.add(item);

    if (tail->array.size() > 10) {
        Node* newNode = new Node(0, nullptr);

        int half = tail->array.size() / 2;
        for (int i = half; i < tail->array.size(); ++i) {
            newNode->array.add(tail->array.get(i));
        }

        for (int i = tail->array.size() - 1; i >= half; --i) {
            tail->array.remove(i);
        }

        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    }
}


template <typename T>
void BalancedList<T>::add(size_t index, const T& item) {
    if (index > totalSize)
        throw std::out_of_range("Index out of bounds");

    if (isEmpty()) {
        head = tail = new Node(initialArraySize);
        head->array.add(item);
        totalSize++;
        return;
    }

    Node* current = head;
    size_t position = index;

    while (position > current->array.size()) {
        position -= current->array.size();
        current = current->next;
    }

    current->array.add(position, item);
    totalSize++;

    if (current->array.size() > current->array.getCapacity()) {
        Node* newNode = new Node(initialArraySize);
        size_t half = current->array.size() / 2;

        for (size_t j = half; j < current->array.size(); ++j) {
            newNode->array.add(current->array.get(j));
        }

        for (size_t j = current->array.size(); j > half; --j) {
            current->array.remove(j - 1);
        }

        newNode->next = current->next;
        current->next = newNode;

        if (current == tail)
            tail = newNode;
    }
}

// Remove and return the first item
template <typename T>
T BalancedList<T>::remove() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    T removedValue = head->array.remove(0);  // remove FRONT element (index 0)

    if (head->array.size() == 0) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }

    if (head == nullptr) {
        tail = nullptr;
    }

    return removedValue;
}

// Remove and return an item at a specific index
template <typename T>
T BalancedList<T>::remove(size_t index) {
    Node* current = head;
    int count = 0;

    while (current != nullptr && index >= current->array.size()) {
        index -= current->array.size();
        current = current->next;
    }

    if (current == nullptr)
        throw std::out_of_range("Invalid index");

    T removedValue = current->array.remove(index);

    if (current->array.size() == 0) {
        if (current == head) {
            head = head->next;
            if (head == nullptr)
                tail = nullptr;
        }
    }

    return removedValue;
}