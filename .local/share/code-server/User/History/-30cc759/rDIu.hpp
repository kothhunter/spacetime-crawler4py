#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <ostream>
#include <utility>

template <typename T>
class Array {
public:
    //construct zero length aray
    Array() : len{0}, buf{nullptr} {}

    //construct array of given length
    explicit Array(int len) : len{len}, buf{new T[len]} {}

    //copy
    Array(const Array& other) : len{other.len}, buf{new T[other.len]} {
        for (int i=0; i<len; ++i){
            buf[i] = other.buf[i];
        }
    }

    //move
    Array(Array&& other) noexcept : len{other.len}, buf{other.buf} {
        other.len = 0;
        other.buf = nullptr;
    }

    //swap
    friend void swap(Array& lhs, Array&rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

   template <typename Fn>
   void fill_with_fn(Fn fn);

private:
   int len;
   T* buf;

   bool in_bounds(int index) const {
   return index >= 0 && index < len;
   }
};


#endif