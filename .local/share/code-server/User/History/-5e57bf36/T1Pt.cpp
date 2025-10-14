#include "triangle.hpp"
#include <algorithm>
#include <iostream>

Triangle::Triangle(Point center, std::string name, int base, int height) 
    : Shape(center, std::move(name)), base(base), height(height) {}

// Computes and returns the area of the Triangle
double Triangle::area() const {
    return 0.5 * base * height;
}

// Draws the Triangle using simple character graphics (placeholder implementation)
void Triangle::draw(std::ostream& out) const {
    out << "Drawing Triangle with base " << base << " and height " << height << "\n";
}

// Creates a new duplicate of this Triangle object
Triangle* Triangle::clone() const {
    return new Triangle(*this);
}
