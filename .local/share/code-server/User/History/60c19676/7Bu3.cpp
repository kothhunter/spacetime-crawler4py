#include "picture.hpp"
#include <iostream>
#include <utility>

Picture::Picture() : head(nullptr), tail(nullptr) {}

Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    for (ListNode* curr = other.head; curr != nullptr; curr = curr->next) {
        add(*curr->shape);
    }
}

Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

Picture::~Picture() {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head->shape;
        delete head;
        head = nextNode;
    }
}

void Picture::swap(Picture& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

Picture& Picture::operator=(const Picture& other) {
    if (this != &other) {
        Picture temp(other); 
        swap(temp); 
    }
    return *this;
}

Picture& Picture::operator=(Picture&& other) {
    if (this != &other) {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp->shape;
            delete temp;
        }

        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

void Picture::add(const Shape& shape) {
    ListNode* newNode = new ListNode{ shape.clone(), nullptr };

    if (!head) {
        head = tail = newNode; 
    } else {
        tail->next = newNode; 
        tail = newNode; 
    }
}

void Picture::print_all(std::ostream& out) const {
    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
        curr->shape->print(out); 
        curr->shape->draw(out);  
    }
}

void Picture::draw_all(std::ostream& out) const {
    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
        curr->shape->draw(out);
    }
}

double Picture::total_area() const {
    double sum = 0;
    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
        sum += curr->shape->area();
    }
    return sum;
}
