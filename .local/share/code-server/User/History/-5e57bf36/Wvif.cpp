#include "triangle.hpp"
#include <algorithm>
#include <iostream>

Triangle::Triangle(Point center, std::string name, int base, int height) 
    : Shape(center, std::move(name)), base(base), height(height) {}

double Triangle::area() const {
    return 0.5 * base * height;
}

void Triangle::draw(std::ostream& out) const {
    out << "Drawing Triangle with base " << base << " and height " << height << "\n";
}

Triangle* Triangle::clone() const {
    return new Triangle(*this);
}
