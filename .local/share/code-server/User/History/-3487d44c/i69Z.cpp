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

String::~String() {
    delete[] buf;
}

void String::swap(String &s) {
    std::swap(buf, s.buf);
}