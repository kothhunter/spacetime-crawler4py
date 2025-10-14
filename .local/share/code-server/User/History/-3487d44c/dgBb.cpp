#include "string.hpp"
#include <utility>  
#include <iostream>

String::String(const char *s) {
    head = list::from_cstring(s);
}

String::String(const String &s) {
    head = copy::
}

String::String(String &&s) {
    swap(s);
    s.buf = nullptr;
}

String::~String() {
    delete[] buf;
}

void String::swap(String &s) {
    std::swap(buf, s.buf);
}