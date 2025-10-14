#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <ostream>
#include <utility>

template <typename T>
class Array {
public:
    Array() : len{0}, buf{nullptr} {}
    

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