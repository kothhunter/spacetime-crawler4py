#ifndef STRING_HPP
#define STRING_HPP

#include <iosfwd>

constexpr int MAXLEN = 1024;

class String {
public:
    explicit String(const char *s = "");
    String(const String &s);
    String &operator=(const String &s);
    
}