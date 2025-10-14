#include "picture.hpp"
#include <iostream>
#include <utility>

Picture::Picture() : head(nullptr), tail(nullptr) {}

// Copy Constructor: Deep copies another Picture's list
Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    for (ListNode* current = other.head; current; current = current->next) {
        add(*current->shape);
    }
}

// Move Constructor: Transfers ownership from another Picture
Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

// Destructor: Cleans up the linked list and deallocates memory
Picture::~Picture() {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp->shape;
        delete temp;
    }
}

// Swap function: Exchanges data between two pics
void Picture::swap(Picture& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

// Copy Assignment: Uses copy-and-swap idiom
Picture& Picture::operator=(const Picture& other) {
    if (this != &other) {
        Picture temp(other); // Copy constructor
        swap(temp); // Swap with temporary copy
    }
    return *this;
}

// Move Assignment: Transfers ownership efficiently
Picture& Picture::operator=(Picture&& other) {
    if (this != &other) {
        // Free current memory
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp->shape;
            delete temp;
        }

        // Move resources
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

// Adds a new shape clone to the end of the linked list
void Picture::add(const Shape& shape) {
    ListNode* newNode = new ListNode{ shape.clone(), nullptr };

    if (!head) {
        head = tail = newNode; // First node in the list
    } else {
        tail->next = newNode; // Append to tail
        tail = newNode; // Update tail pointer
    }
}

// Calls `print()` on each shape in order
void Picture::print_all(std::ostream& out) const {
    for (ListNode* current = head; current; current = current->next) {
        current->shape->print(out);
    }
}

// Calls `draw()` on each shape in order
void Picture::draw_all(std::ostream& out) const {
    for (ListNode* current = head; current; current = current->next) {
        current->shape->draw(out);
    }
}

// Computes and returns the total area of all shapes in the Picture
double Picture::total_area() const {
    double sum = 0;
    for (ListNode* current = head; current; current = current->next) {
        sum += current->shape->area();
    }
    return sum;
}
