#include "string.hpp"
#include <iostream>
#include <cassert>

String::String(const char *s) {
    if (strlen(s) >= MAXLEN) {
        std::cerr << "ERROR: Input string exceeds maximum length" << std::endl;
        buf[0] = '\0'; 
    } else {
        strncpy(buf, s, MAXLEN - 1);
    }
}

String::String(const String &s) {
    strncpy(buf, s.buf, MAXLEN - 1);
}

String &String::operator=(const String &s) {
    if (this != &s) { 
        strncpy(buf, s.buf, MAXLEN - 1);
    }
    return *this;
}
String &String::operator=(const String &s) {
    if (this != &s) { // Check for self-assignment
        if (strlen(s.buf) >= MAXLEN) {
            std::cerr << "ERROR: Input string exceeds maximum length" << std::endl;
            buf[0] = '\0'; // Set the buffer to an empty string
        } else {
            strncpy(buf, s.buf, MAXLEN - 1);
        }
    }
    return *this;
}

char &String::operator[](int index) {
    assert(in_bounds(index)); 
    return buf[index];
}

int String::size() {
    return strlen(buf);
}

String String::reverse() {
    char temp[MAXLEN];
    reverse_cpy(temp, buf);
    return String(temp);
}

int String::indexOf(char c) {
    const char *result = strchr(buf, c);
    return result ? result - buf : -1;
}

int String::indexOf(const String &s) {
    const char *result = strstr(buf, s.buf);
    return result ? result - buf : -1;
}

bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
    return strcmp(buf, s.buf) >= 0;
}

String String::operator+(const String &s) {
    char temp[MAXLEN];
    strcpy(temp, buf);
    strncat(temp, s.buf, MAXLEN - strlen(buf) - 1);
    return String(temp);
}

String &String::operator+=(const String &s) {
    int current_len = strlen(buf);
    int remaining_space = MAXLEN - current_len - 1;
    if (remaining_space > 0) {
        strncat(buf, s.buf, remaining_space);
    }
    return *this;
}

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    // in.getline(buf, MAXLEN);
    in >> buf;
}

String::~String() {

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
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
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
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int dest_len = strlen(dest);
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[dest_len + i] = src[i];
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
    for (int i = 0; i < n; ++i) {
        if (left[i] != right[i]) {
            return left[i] - right[i];
        }
        if (left[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}

const char *String::strchr(const char *str, char c) {
    while (*str) {
        if (*str == c) {
            return str;
        }
        str++;
    }
    if (c == '\0') {
        return str;
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

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}