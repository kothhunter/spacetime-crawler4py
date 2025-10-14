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