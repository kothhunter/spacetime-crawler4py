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

    //copy constr
    Array(const Array& other) : len{other.len}, buf{new T[other.len]} {
        for (int i=0; i<len; ++i){
            buf[i] = other.buf[i];
        }
    }

    //move constr
    Array(Array&& other) noexcept : len{other.len}, buf{other.buf} {
        other.len = 0;
        other.buf = nullptr;
    }

    //swap
    friend void swap(Array& lhs, Array&rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    //copy assign
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            swap(*this, temp);
        }
        return *this;
    }

    // move assign
    Array& operator=(Array&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    // destr
    ~Array() {
        delete[] buf;
    }

    // length of the array
    int length() const {
        return len;
    }

    // get a particular element of the array (non-const)
    T& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    // '''' (const)
    const T& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    // set every element of the array to `val`
    void fill(T val) {
        for (int i = 0; i < len; ++i) {
            buf[i] = val;
        }
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