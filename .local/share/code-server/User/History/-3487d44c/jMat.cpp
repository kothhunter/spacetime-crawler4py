#include "string.hpp"
#include <utility>  
#include <iostream>

String::String(const char *s) {
    head = list::from_string(s);
}

String::String(const String &s) {
    head = list::copy(s.head);
}

String::String(String &&s) {
    head = s.head;
    s.head = nullptr;
}

String::String(list::Node* new_head) {
    head = new_head;
}

String::~String() {
    list::free(head);
}

void String::swap(String &s) {
    std::swap(head, s.head);
}

//copy assignment
String &String::operator=(const String &s) {
    if (this != &s) {
        list::free(head);
        head = list::copy(s.head);
    }
    return *this;
}

//move assignment
String &String::operator=(String &&s) {
    if (this != &s) {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

char String::operator[](int index) const {
    list::Node* node = list::nth(head, index);
    return node ? node->data : '\0';
}

int String::size() const {
    return list::length(head);
}

bool String::operator==(const String &s) const {
    return list::compare(head, s.head) == 0;
}

strong_ordering String::operator<=>(const String &s) const {
    return list::compare(head, s.head) <=> 0;
}