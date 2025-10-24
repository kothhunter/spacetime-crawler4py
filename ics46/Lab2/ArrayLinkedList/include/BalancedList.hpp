#ifndef BalancedList_HPP
#define BalancedList_HPP

#include "ArrayList.hpp"
#include <stdexcept>
#include <iostream>

template <typename T>
class BalancedList {
private:
    class Node {
    public:
        ArrayList<T> array; // Use ArrayList for internal storage
        Node* next;

        Node(size_t arraySize, Node* next = nullptr)
            : array(arraySize), next(next) {}
    };

    Node* head;
    Node* tail;
    size_t initialArraySize; // Initial size of the ArrayList 
    size_t totalSize;        // Total number of elements in the BalancedList

    void rangeCheck(size_t index) const;
    void clear(); // Helper function to clear the list

public:
    BalancedList(size_t initialArraySize = 10); // Constructor with default initial array size
    ~BalancedList();                            // Destructor to free memory
    BalancedList(const BalancedList<T>& other); // Copy constructor
    BalancedList<T>& operator=(const BalancedList<T>& other); // Copy assignment operator

    // Operations
    bool isEmpty() const;                // Returns true if the BalancedList is empty
    size_t size() const;                 // Returns the total number of elements
    T get(size_t index) const;           // Retrieves an item by index
    void add(const T& item);             // Adds an item to the front of the list
    void add(size_t index, const T& item); // Adds an item at a specific index
    T remove();                          // Removes and returns the first item
    T remove(size_t index);              // Removes and returns an item at a specific index
};

#include "BalancedList.tpp" // Include the implementation file

#endif // BalancedList_HPP