#include "string.hpp"
#include <utility>  
#include <iostream>

// Constructs this string from a C string, defaults to empty string
String::String(const char *s) {
    buf = strdup(s);
    buf[strlen(s)] = '\0';
}

// Constructs this string as a copy of string s
String::String(const String &s) {
    buf = strdup(s.buf);
    buf[s.size()] = '\0';
}

// Constructs this string by moving from string s
String::String(String &&s) {
    swap(s);
    s.buf = nullptr;
}

// Destructor for this string
String::~String() {
    delete[] buf;
}

// Swap buf between this string and s using std::swap
void String::swap(String &s) {
    std::swap(buf, s.buf);
}

String &String::operator=(String &&s) {
    delete[] buf;
    swap(s);
    s.buf = nullptr;
    return *this;
}
// Assignment operator from one string, s, to this string
String &String::operator=(String &s) {
    String temp(s);
    swap(temp);
    delete[] temp.buf;
    temp.buf = nullptr;
    return *this;
}

// Allow indexing this string with notation s[i]
char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cout << "Error";
    }
    else{
        return buf[index];
    }
    return buf[0];
}

// Allow const indexing
const char &String::operator[](int index) const {
    if (!in_bounds(index)) {
        std::cout << "Error";
    }
    else{
        return buf[index];
    }
    return buf[0];
}

// Returns the logical length of this string (# of chars up to '\0')
int String::size() const {
    return strlen(buf);
}

// Returns a reversal of this string, does not modify this string
String String::reverse() const {
    String reversed(size());
    reverse_cpy(reversed.buf, buf);
    return reversed;
}

// Returns index into this string for first occurrence of c
int String::indexOf(char c) const {
    const char *ptr = strchr(buf, c);
    return ptr ? ptr - buf : -1;
}

// Returns index into this string for first occurrence of s
int String::indexOf(String s) const {
    const char *ptr = strstr(buf, s.buf);
    return ptr ? ptr - buf : -1;
}

// Relational operators for comparing this strings to another string
bool String::operator==(String s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(String s) const {
    // return !(*this == s);
    return strcmp(buf, s.buf) != 0;
}

bool String::operator>(String s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<(String s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(String s) const {
    return !(*this > s);
}

bool String::operator>=(String s) const {
    return !(*this < s);
}

// Concatenate this and s to form a return string
String String::operator+(String s) const {
    String result(size() + s.size());
    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);
    return result;
}

// Concatenate s onto the end of this string
String &String::operator+=(String s) {
    char * add = new char[size() + s.size() + 1];
    strcpy(add, buf);
    strcat(add, s.buf);
    delete[] buf;
    buf = add;
    return *this;
}

// Print this string
void String::print(std::ostream &out) const {
    out << buf;
}

// Read next word into this string
void String::read(std::istream &in) {
    char temp[1024];
    in >> temp;
    delete[] buf;
    buf = strdup(temp);
}

// Static helper methods

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
    while (i < n && (dest[i] = src[i]) != '\0') {
        i++;
    }
    while (i < n) {
        dest[i++] = '\0';
    }
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
    int needle_len = strlen(needle);
    while (*haystack) {
        if (strncmp(haystack, needle, needle_len) == 0) {
            return haystack;
        }
        haystack++;
    }
    return nullptr;
}

// Private constructor to create a String object with an array of a specified size
String::String(int length) {
    buf = new char[length + 1];
    buf[length] = '\0';
}

// Overloaded output operator
std::ostream &operator<<(std::ostream &out, String s) {
    s.print(out);
    return out;
}

// Overloaded input operator
std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}