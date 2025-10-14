#ifndef STRING_HPP
#define STRING_HPP

#include <iosfwd>

constexpr int MAXLEN = 1024;

class String {
public:
    explicit String(const char *s = "");

    String(const String &s);

    String &operator=(const String &s);

    char &operator[](int index);
    
    int size();
    
    String reverse();
    
    int indexOf(char c);
    
    int indexOf(const String &s);

    bool operator ==(const String &s) const;
    bool operator !=(const String &s) const;
    bool operator >(const String &s) const;
    bool operator <(const String &s) const;
    bool operator <=(const String &s) const;
    bool operator >=(const String &s) const;
}