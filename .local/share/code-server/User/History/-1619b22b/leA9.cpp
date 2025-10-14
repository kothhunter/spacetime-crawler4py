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

// String &String::operator=(String &&s) {
//     if (this != &s) { 
//         delete[] buf;
//         swap(s);
//         s.buf = nullptr;
//     }
//     return *this;
// }

String &String::operator=(const String &s) {
    if (this != &s) {
        String temp(s);
        swap(temp);
    }
    return *this;
}

char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cout << "ERROR";
    }
    else{
        return buf[index];
    }
    return buf[0];
}

const char &String::operator[](int index) const {
    if (!in_bounds(index)) {
        std::cout << "ERROR";
    }
    else{
        return buf[index];
    }
    return buf[0];
}

int String::size() const {
    return strlen(buf);
}

String String::reverse() const {
    String reversed(size());
    reverse_cpy(reversed.buf, buf);
    return reversed;
}

int String::indexOf(char c) const {
    const char *ptr = strchr(buf, c);
    return ptr ? ptr - buf : -1;
}

int String::indexOf(const String &s) const {
    const char *ptr = strstr(buf, s.buf);
    return ptr ? ptr - buf : -1;
}

bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    // return !(*this == s);
    return strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
    return !(*this > s);
}

bool String::operator>=(const String &s) const {
    return !(*this < s);
}

String String::operator+(String s) const {
    String result(size() + s.size());
    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);
    return result;
}

String &String::operator+=(String s) {
    char * add = new char[size() + s.size() + 1];
    strcpy(add, buf);
    strcat(add, s.buf);
    delete[] buf;
    buf = add;
    return *this;
}

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    char temp[1024];
    in >> temp;
    delete[] buf;
    buf = strdup(temp);
}

int String::strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') {
        i++;
    }
    return dest;
}

char *String::strdup(const char *src) {
    int len = strlen(src);
    char *dest = new char[len + 1];
    strcpy(dest, src);
    return dest;
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for (; src[i] != '\0' && i < n; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int dest_len = strlen(dest);
    int i = 0;
    while ((dest[dest_len + i] = src[i]) != '\0') {
        i++;
    }
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int dest_len = strlen(dest);
    int i = 0;
    while (i < n && (dest[dest_len + i] = src[i]) != '\0') {
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right) {
    while (*left && *right && *left == *right) {
        left++;
        right++;
    }
    return *left - *right;
}

int String::strncmp(const char *left, const char *right, int n) {
    while (n-- && *left && *right && *left == *right) {
        left++;
        right++;
    }
    return n < 0 ? 0 : *left - *right;
}

void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}

const char *String::strchr(const char *str, char c) {
    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }
    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return haystack;
    }
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (*n == '\0') {
            return haystack;
        }
        haystack++;
    }
    return nullptr;
}

String::String(int length) {
    buf = new char[length + 1];
    buf[length] = '\0';
}

std::ostream &operator<<(std::ostream &out, String s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}