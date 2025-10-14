#include "string.hpp"
#include <utility>  
#include <iostream>

String::String(const char *s) {
    buf = strdup(s);
    buf[strlen(s)] = '\0';
}

String::String(const String &s) {
    buf = strdup(s.buf);
    buf[s.size()] = '\0';
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