#include "BalancedList.hpp"

// Constructor
template <typename T>
BalancedList<T>::BalancedList(size_t initialArraySize)
    : head(nullptr), tail(nullptr), initialArraySize(initialArraySize), totalSize(0) {}

// Destructor
template <typename T>
BalancedList<T>::~BalancedList() {
    // TODO: implement destructor

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
    // TODO: implement get with time complexity O(log n) where n is the number of elements


}

// Add an item to the front of the list
template <typename T>
void BalancedList<T>::add(const T& item) {
    // TODO: implement add with amortized time complexity O(1)


}

template <typename T>
void BalancedList<T>::add(size_t index, const T& item) {
    // TODO: implement add at index 
    // with worst case time complexity O(n) where n is the number of elements
    // For full credit, BalancedList should perform better than both ArrayList and SinglyLinkedList 
    // in the experiment provided in main.cpp
    
    
}


// Remove and return the first item
template <typename T>
T BalancedList<T>::remove() {
    // TODO: implement remove with time complexity O(1)
    
}

// Remove and return an item at a specific index
template <typename T>
T BalancedList<T>::remove(size_t index) {
    // TODO: implement remove at index
    // with worst case time complexity O(n) where n is the number of elements
    // For full credit, BalancedList should perform better than both ArrayList and SinglyLinkedList 
    // in the experiment provided in main.cpp

}