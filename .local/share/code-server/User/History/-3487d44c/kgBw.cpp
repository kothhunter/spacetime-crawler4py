#include "string.hpp"
#include <utility>  
#include <iostream>

String::String(const char *s) {
    buf = strdup(s);
    buf[strlen(s)] = '\0';
}